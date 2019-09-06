
/**************************************************************
Copyright(c) 2019 Angelo Coppi

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files(the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions :

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
********************************************************************/
#include "calogiface.h"
#include "cacakemanager.h"
#include "calayerconf.h"
#include "cajobstep.h"
#include "cajoblayer.h"
#include "cautils.h"
#include "castatusconf.h"
#include <caconfenv.h>
#include <cstdlib>


namespace CA
{

caJobLayer::~caJobLayer()
{
    jobstep=nullptr;
    for (auto & st: projects_status )
    {
        auto * status = dynamic_cast<CAXml_Status*>(st.second->st);
        delete status;
        delete st.second;
    }
    projects_status.clear();
}

void caJobLayer::prepareScripts()
{
    std::string replaced;
    jobstep->getEnv()->getValue("REPO",replaced);
    if(!caUtils::checkDirExist(replaced))
    {
        std::stringstream ss;
        ss<<"REPO dir "<<replaced<<"not exit"<<std::endl;
        std::string msg=ss.str();
        sys_throw(msg);
    }
    prepareProjectScripts(replaced);
}


void caJobLayer::prepareProjectScripts(std::string &repo)
{
    auto result=0;
    auto *layer = dynamic_cast<CAXml_Layer *>(jobstep->getLayer());
    LogInfo ("---------------------------------------");
    LogInfo ("Check projetcs scripts files ....");
    LogInfo ("---------------------------------------");
    if(layer_name.empty())
    {
        auto * step= dynamic_cast<CAXml_Main_Defaults_Step *>(jobstep->getStep());
        caUtils::baseNameNoExt(step->layer,layer_name);
    }
    for(auto & prj: layer->include)
    {
        std::string projconf=repo;
        caUtils::appendPath(projconf,prj);
        std::string defaultconf("conf.xml");
        caUtils::appendPath(projconf,defaultconf);
        if(!caUtils::checkFileExist(projconf))
        {
            std::stringstream ss;
            ss<<layer_name<<" : project : "<<prj<<"("<<projconf<<") : Cannot load conf.xml"<<std::endl;
            std::string msg=ss.str();
            sys_throw(msg);
        }
        auto it=projects_status.find(prj);
        if(it==projects_status.end())
        {
            auto *ns=new prjStatus;
            ns->name=prj;
            ns->fullprojconf=projconf;
            ns->st=nullptr;
            std::pair<std::string,prjStatus *> pv(prj,ns);
            projects_status.insert(pv);
            ICAjob_make_script *generator=nullptr;
            ns->phase=ST_NONE;
            while(ns->phase!=ST_COMPLETE)
            {
                setCurrentScript(ns);
                switch(ns->phase)
                {
                case  ST_NONE:
                    LogInfo("%s: starting generate scripts for project : %s",
                            layer_name.c_str() , ns->name.c_str());
                    break;
                case  ST_SOURCE:
                    if(ns->pSource!=ST_SOURCE_NONE)
                    {
                        generator=new caJobMakeSourceScript();
                    }
                    break;
                case  ST_BUILD:
                    if(ns->pBuild!=ST_BUILD_NONE)
                    {
                        generator=new caJobMakeBuildScript();
                    }
                    break;
                case  ST_PACKAGE:
                    if(ns->pPackage!=ST_PACKAGE_NONE)
                    {
                        generator=new caJobMakePackageScript();
                    }
                    break;
                case  ST_DEPLOY:
                    if(ns->pDeploy!=ST_DEPLOY_NONE)
                    {
                        generator=new caJobMakeDeployScript();
                    }
                    break;
                case ST_COMPLETE:
                    LogInfo("%s: generate scripts for project : %s coplete",
                            layer_name.c_str() , ns->name.c_str());
                    break;
                }
                if(generator)
                {
                    generator->create(this,jobstep->getEnv(),ns);
                    delete generator;
                    generator=nullptr;
                }
                setNextStep(ns);
            }
            ns->phase=ST_NONE;
            ns->pSource=ST_SOURCE_NONE;
            ns->pBuild=ST_BUILD_NONE;
            ns->pPackage=ST_PACKAGE_NONE;
            ns->pDeploy=ST_DEPLOY_NONE;
            ns->next_exec="";
        }
    }
}

size_t caJobLayer::loadLayerStatus(std::list<std::string > & order)
{
    std::string replaced;
    std::string replaced_prj;
    jobstep->getEnv()->getValue("STATUS",replaced);
    jobstep->getEnv()->getValue("REPO",replaced_prj);
    caUtils::checkDirExistOrCreate(replaced);
    if(!caUtils::checkDirExist(replaced_prj))
    {
        std::stringstream ss;
        ss<<"REPO dir "<<replaced_prj<<"not exit"<<std::endl;
        std::string msg=ss.str();
        sys_throw(msg);
    }
    if(layer_name.empty())
    {
        auto * step= dynamic_cast<CAXml_Main_Defaults_Step *>(jobstep->getStep());
        caUtils::baseNameNoExt(step->layer,layer_name);
    }
    caUtils::appendPath(replaced,layer_name);
    caUtils::checkDirExistOrCreate(replaced);
    return  loadProjectsStatus(order,replaced, replaced_prj,layer_name);
}

size_t caJobLayer::loadProjectsStatus(std::list<std::string > & order,std::string & path,
                                      std::string & repo,std::string & layer_name)
{
    auto result=0;
    order.clear();
    auto *layer = dynamic_cast<CAXml_Layer *>(jobstep->getLayer());
    LogInfo ("---------------------------------------");
    LogInfo ("Verifyng working projetcs status ....");
    LogInfo ("---------------------------------------");
    for(auto & prj: layer->include)
    {
        std::string p_status_name = prj+".xml";
        std::string p_status=path;
        std::string projconf=repo;
        caUtils::appendPath(projconf,prj);
        std::string defaultconf("conf.xml");
        caUtils::appendPath(projconf,defaultconf);
        caUtils::appendPath(p_status,p_status_name);
        if(!caUtils::checkFileExist(projconf))
        {
            std::stringstream ss;
            ss<<layer_name<<" : project : "<<prj<<"("<<projconf<<") : Cannot load conf.xml"<<std::endl;
            std::string msg=ss.str();
            sys_throw(msg);
        }
        if(!caUtils::compareFileChangeDate(projconf,p_status))
        {
            // project conf file is newer than status file : remove status file
            LogInfo("%s:project configuration %s was changed : invalidate status ",
                    layer_name.c_str(),prj.c_str());
            remove(p_status.c_str());
        }
        if(caUtils::checkFileExist(p_status))
        {
            auto it=projects_status.find(prj);
            if(it!=projects_status.end())
            {
                LogInfo("%s:Loading  project %s status ",layer_name.c_str(),prj.c_str());
                if(it->second->st==nullptr)
                {
                    it->second->st=new CAXml_Status();
                    it->second->st->loadFromXml(p_status);
                    it->second->fullpath=p_status;
                }
            }
            else
            {
                std::stringstream ss;
                ss<<layer_name<<" : project : "<< prj <<" Cannot find status objects";
                std::string msg=ss.str();
                sys_throw(msg);
            }
        }
        else
        {
            LogInfo("%s:Status file  for project %s not available ,create ",
                    layer_name.c_str(),prj.c_str());
            ICAXml_Status *status =new CAXml_Status();
            std::ofstream f(p_status);
            std::stringstream ss;
            status->toString(ss);
            f<<ss.str().c_str();
            f.close();
            auto nit=projects_status.find(prj);
            if(nit!=projects_status.end())
            {
                LogInfo("%s:Loading  project %s status ",layer_name.c_str(),prj.c_str());
                nit->second->st=status;
                nit->second->fullpath=p_status;
            }
            else
            {
                std::stringstream ss;
                ss<<layer_name<<" : project : "<< prj <<" Cannot find status objects";
                std::string msg=ss.str();
                sys_throw(msg);
            }
        }

    }
    for(auto & prj: layer->include)
    {
        auto it=projects_status.find(prj);
        if(it!=projects_status.end())
        {
            getNextExec(it->second);
            if(it->second->phase!=ST_COMPLETE)
            {
                LogInfo("%s : project : %s : next exec : %s",
                        layer_name.c_str(), prj.c_str(), it->second->next_exec.c_str());
                result++;
                order.push_back(prj);
            }
            else
                LogInfo("%s : project : %s : completed ",
                        layer_name.c_str(),prj.c_str());
        }
        else
        {
            std::stringstream ss;
            ss<<layer_name<<" : project : "<<prj<<"Cannot find current status"<<std::endl;
            std::string msg=ss.str();
            sys_throw(msg);
        }
    }
    LogInfo("%s : Total Projects to work %ld",layer_name.c_str(),result);
    return result;
}

void caJobLayer::getNextExec(prjStatus *st)
{
    if (st)
    {
        st->phase=ST_NONE;
        st->pSource=ST_SOURCE_NONE;
        st->pBuild=ST_BUILD_NONE;
        st->pPackage=ST_PACKAGE_NONE;
        st->pDeploy=ST_DEPLOY_NONE;
        CAXml_Status *cur = dynamic_cast<CAXml_Status *>(st->st);
        if(cur)
        {
            if(cur->pre_download!="1")
            {
                st->phase=ST_SOURCE;
                st->pSource=ST_SOURCE_PRE_DOWNLOAD;
            }
            else if(cur->download!="1")
            {
                st->phase=ST_SOURCE;
                st->pSource=ST_SOURCE_DOWNLOAD;
            }
            else if(cur->post_download!="1")
            {
                st->phase=ST_SOURCE;
                st->pSource=ST_SOURCE_POST_DOWNLOAD;
            }
            else if(cur->pre_patch!="1")
            {
                st->phase=ST_SOURCE;
                st->pSource=ST_SOURCE_PRE_PATCH;
            }
            else if(cur->patch!="1")
            {
                st->phase=ST_SOURCE;
                st->pSource=ST_SOURCE_PATCH;
            }
            else if(cur->post_patch!="1")
            {
                st->phase=ST_SOURCE;
                st->pSource=ST_SOURCE_POST_PATCH;
            }
            else if(cur->pre_save_source!="1")
            {
                st->phase=ST_SOURCE;
                st->pSource=ST_SOURCE_PRE_SAVE;
            }
            else if(cur->save_source!="1")
            {
                st->phase=ST_SOURCE;
                st->pSource=ST_SOURCE_SAVE;
            }
            else if(cur->post_save_source!="1")
            {
                st->phase=ST_SOURCE;
                st->pSource=ST_SOURCE_POST_SAVE;
            }
            else if(cur->pre_configure!="1")
            {
                st->phase=ST_BUILD;
                st->pBuild=ST_BUILD_PRE_CONFIGURE;
            }
            else if(cur->configure!="1")
            {
                st->phase=ST_BUILD;
                st->pBuild=ST_BUILD_CONFIGURE;
            }
            else if(cur->post_configure!="1")
            {
                st->phase=ST_BUILD;
                st->pBuild=ST_BUILD_POST_CONFIGURE;
            }
            else if(cur->pre_build!="1")
            {
                st->phase=ST_BUILD;
                st->pBuild=ST_BUILD_PRE_BUILD;
            }
            else if(cur->build!="1")
            {
                st->phase=ST_BUILD;
                st->pBuild=ST_BUILD_BUILD;
            }
            else if(cur->post_build!="1")
            {
                st->phase=ST_BUILD;
                st->pBuild=ST_BUILD_POST_BUILD;
            }
            else if(cur->pre_install!="1")
            {
                st->phase=ST_BUILD;
                st->pBuild=ST_BUILD_PRE_INSTALL;
            }
            else if(cur->install!="1")
            {
                st->phase=ST_BUILD;
                st->pBuild=ST_BUILD_INSTALL;
            }
            else if(cur->post_install!="1")
            {
                st->phase=ST_BUILD;
                st->pBuild=ST_BUILD_POST_INSTALL;
            }
            else if(cur->pre_package!="1")
            {
                st->phase=ST_PACKAGE;
                st->pPackage=ST_PACKAGE_PRE;
            }
            else if(cur->package!="1")
            {
                st->phase=ST_PACKAGE;
                st->pPackage=ST_PACKAGE_PACKAGE;
            }
            else if(cur->post_package!="1")
            {
                st->phase=ST_PACKAGE;
                st->pPackage=ST_PACKAGE_POST;
            }
            else if(cur->pre_deploy!="1")
            {
                st->phase=ST_DEPLOY;
                st->pDeploy=ST_DEPLOY_PRE;
            }
            else if(cur->deploy!="1")
            {
                st->phase=ST_DEPLOY;
                st->pDeploy=ST_DEPLOY_IMAGE;
            }
            else if(cur->post_deploy!="1")
            {
                st->phase=ST_DEPLOY;
                st->pDeploy=ST_DEPLOY_POST;
            }
            else
            {
                st->phase=ST_COMPLETE;
            }
            setCurrentScript(st);
        }
    }
}

void caJobLayer::setCurrentScript(prjStatus *st)
{
    const char * source_script_name[]=
    {
        "",
        "pre_download.sh",
        "download.sh",
        "post_download.sh",
        "pre_patch.sh",
        "patch.sh",
        "post_patch.sh",
        "pre_save.sh",
        "save.sh",
        "post_save.sh",
    };
    const char * build_script_name[]=
    {
        "",
        "pre_configure.sh",
        "configure.sh",
        "post_configure.sh",
        "pre_build.sh",
        "build.sh",
        "post_build.sh",
        "pre_install.sh",
        "install.sh",
        "post_install.sh",
    };
    const char * package_script_name[]=
    {
        "",
        "pre_package.sh",
        "package.sh",
        "post_package.sh",
    };
    const char * deploy_script_name[]=
    {
        "",
        "pre_deploy.sh",
        "deploy.sh",
        "post_deploy.sh",
    };
    if (st)
    {
        st->next_exec.clear();
        switch(st->phase)
        {
        case ST_COMPLETE:
        case ST_NONE:
            break;
        case ST_SOURCE:
            st->next_exec=source_script_name[st->pSource];
            break;
        case ST_BUILD:
            st->next_exec=build_script_name[st->pBuild];
            break;
        case ST_PACKAGE:
            st->next_exec=package_script_name[st->pPackage];
            break;
        case ST_DEPLOY:
            st->next_exec=deploy_script_name[st->pDeploy];
            break;
        }
    }
}

void caJobLayer::setNextStep(prjStatus *st)
{
    if (st)
    {
        switch(st->phase)
        {
        case ST_COMPLETE:
            break;
        case ST_NONE:
            st->phase=ST_SOURCE;
            st->pSource=ST_SOURCE_NONE;
            st->pBuild=ST_BUILD_NONE;
            st->pPackage=ST_PACKAGE_NONE;
            st->pDeploy=ST_DEPLOY_NONE;
            break;
        case ST_SOURCE:
            if(st->pSource==ST_SOURCE_POST_SAVE)
            {
                st->phase=ST_BUILD;
                st->pSource=ST_SOURCE_NONE;
                st->pBuild=ST_BUILD_NONE;
            }
            else
            {
                unsigned int v=(unsigned int )st->pSource;
                v++;
                st->pSource=(prjPhaseSource)v;
            }
            break;
        case ST_BUILD:
            if(st->pBuild==ST_BUILD_POST_INSTALL)
            {
                st->phase=ST_PACKAGE;
                st->pBuild=ST_BUILD_NONE;
                st->pPackage=ST_PACKAGE_NONE;

            }
            else
            {
                unsigned int v=(unsigned int )st->pBuild;
                v++;
                st->pBuild=(prjPhaseBuild)v;
            }
            break;
        case ST_PACKAGE:
            if(st->pPackage==ST_PACKAGE_POST)
            {
                st->phase=ST_DEPLOY;
                st->pPackage=ST_PACKAGE_NONE;
                st->pDeploy=ST_DEPLOY_NONE;
            }
            else
            {
                unsigned int v=(unsigned int )st->pPackage;
                v++;
                st->pPackage=(prjPhasePackage)v;
            }
            break;
        case ST_DEPLOY:
            if(st->pDeploy==ST_DEPLOY_POST)
            {
                st->phase=ST_COMPLETE;
                st->pDeploy=ST_DEPLOY_NONE;
            }
            else
            {
                unsigned int v=(unsigned int )st->pDeploy;
                v++;
                st->pDeploy=(prjPhaseDeploy)v;
            }
            break;
        }
    }
}


}