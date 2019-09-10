
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
#include "cainterfaces.h"
#include "calogiface.h"
#include "calogger.h"
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
        auto * status = static_cast<CAXml_Status*>(st.second->getXmlStatus());
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
    if(layer_name.empty())
    {
        auto * step= dynamic_cast<CAXml_Main_Defaults_Step *>(jobstep->getStep());
        caUtils::baseNameNoExt(step->layer,layer_name);
    }
    std::string logdir;
    jobstep->getEnv()->getValue("LOGS",logdir);
    std::string logfile=logdir;
    std::string lname(layer_name);
    lname+="_scripts.log";
    caUtils::appendPath(logfile,lname);
    FilePrinter printer (logfile.c_str());
    CA::ILogger::getInstance()->addOutput(&printer);
    prepareProjectScripts(replaced);
    CA::ILogger::getInstance()->sync();
    CA::ILogger::getInstance()->removeOutput(&printer);
}


void caJobLayer::prepareProjectScripts(std::string &repo)
{
    auto result=0;
    auto *layer = dynamic_cast<CAXml_Layer *>(jobstep->getLayer());
    LogInfo ("---------------------------------------");
    LogInfo ("Check projetcs scripts files ....");
    LogInfo ("---------------------------------------");
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
            auto *ns=new caPrjStatus(prj,projconf);
            std::pair<std::string,IPrjStatus *> pv(prj,ns);
            projects_status.insert(pv);
            ICAjob_make_script *generator=nullptr;
            while(ns->getMainPhase()!=ST_COMPLETE)
            {
                setCurrentScript(ns);
                switch(ns->getMainPhase())
                {
                case  ST_NONE:
                    LogInfo("%s: starting generate scripts for project : %s",
                            layer_name.c_str() , ns->getName().c_str());
                    break;
                case  ST_SOURCE:
                    if(ns->getPhaseSource()!=ST_SOURCE_NONE)
                    {
                        generator=new caJobMakeSourceScript();
                    }
                    break;
                case  ST_BUILD:
                    if(ns->getPhaseBuild()!=ST_BUILD_NONE)
                    {
                        generator=new caJobMakeBuildScript();
                    }
                    break;
                case  ST_PACKAGE:
                    if(ns->getPhasePackage()!=ST_PACKAGE_NONE)
                    {
                        generator=new caJobMakePackageScript();
                    }
                    break;
                case  ST_DEPLOY:
                    if(ns->getPhaseDeploy()!=ST_DEPLOY_NONE)
                    {
                        generator=new caJobMakeDeployScript();
                    }
                    break;
                case ST_COMPLETE:
                    LogInfo("%s: generate scripts for project : %s coplete",
                            layer_name.c_str() , ns->getName().c_str());
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
                LogInfo("%s : Loading  project %s status ",layer_name.c_str(),prj.c_str());
                if(it->second->getXmlStatus()==nullptr)
                {
                    CAXml_Status *xml=new CAXml_Status();
                    it->second->setXmlStatus(xml);
                    xml->loadFromXml(p_status);
                    it->second->setFullPath(p_status);
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
                LogInfo("%s : Loading  project %s status ",layer_name.c_str(),prj.c_str());
                nit->second->setXmlStatus(status);
                nit->second->setFullPath(p_status);
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
            if(it->second->getMainPhase()!=ST_COMPLETE)
            {
                LogInfo("%s : project : %s : next exec : %s",
                        layer_name.c_str(), prj.c_str(), it->second->getNextExec().c_str());
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

void caJobLayer::getNextExec(IPrjStatus *st)
{
    if (st)
    {
        st->clearAllStatus();
        CAXml_Status *cur = static_cast<CAXml_Status *>(st->getXmlStatus());
        if(cur)
        {
            if(cur->pre_download!="1")
            {
                st->setPhaseSource(ST_SOURCE_PRE_DOWNLOAD);
            }
            else if(cur->download!="1")
            {
                st->setPhaseSource(ST_SOURCE_DOWNLOAD);
            }
            else if(cur->post_download!="1")
            {
                st->setPhaseSource(ST_SOURCE_POST_DOWNLOAD);
            }
            else if(cur->pre_patch!="1")
            {
                st->setPhaseSource(ST_SOURCE_PRE_PATCH);
            }
            else if(cur->patch!="1")
            {
                st->setPhaseSource(ST_SOURCE_PATCH);
            }
            else if(cur->post_patch!="1")
            {
                st->setPhaseSource(ST_SOURCE_POST_PATCH);
            }
            else if(cur->pre_save_source!="1")
            {
                st->setPhaseSource(ST_SOURCE_PRE_SAVE);
            }
            else if(cur->save_source!="1")
            {
                st->setPhaseSource(ST_SOURCE_SAVE);
            }
            else if(cur->post_save_source!="1")
            {
                st->setPhaseSource(ST_SOURCE_POST_SAVE);
            }
            else if(cur->pre_configure!="1")
            {
                st->setPhaseBuild(ST_BUILD_PRE_CONFIGURE);
            }
            else if(cur->configure!="1")
            {
                st->setPhaseBuild(ST_BUILD_CONFIGURE);
            }
            else if(cur->post_configure!="1")
            {
                st->setPhaseBuild(ST_BUILD_POST_CONFIGURE);
            }
            else if(cur->pre_build!="1")
            {
                st->setPhaseBuild(ST_BUILD_PRE_BUILD);
            }
            else if(cur->build!="1")
            {
                st->setPhaseBuild(ST_BUILD_BUILD);
            }
            else if(cur->post_build!="1")
            {
                st->setPhaseBuild(ST_BUILD_POST_BUILD);
            }
            else if(cur->pre_install!="1")
            {
                st->setPhaseBuild(ST_BUILD_PRE_INSTALL);
            }
            else if(cur->install!="1")
            {
                st->setPhaseBuild(ST_BUILD_INSTALL);
            }
            else if(cur->post_install!="1")
            {
                st->setPhaseBuild(ST_BUILD_POST_INSTALL);
            }
            else if(cur->pre_package!="1")
            {
                st->setPhasePackage(ST_PACKAGE_PRE);
            }
            else if(cur->package!="1")
            {
                st->setPhasePackage(ST_PACKAGE_PACKAGE);
            }
            else if(cur->post_package!="1")
            {
                st->setPhasePackage(ST_PACKAGE_POST);
            }
            else if(cur->pre_deploy!="1")
            {
                st->setPhaseDeploy(ST_DEPLOY_PRE);
            }
            else if(cur->deploy!="1")
            {
                st->setPhaseDeploy(ST_DEPLOY_IMAGE);
            }
            else if(cur->post_deploy!="1")
            {
                st->setPhaseDeploy(ST_DEPLOY_POST);
            }
            else
            {
                st->setMainPhase(ST_COMPLETE);
            }
            setCurrentScript(st);
        }
    }
}

void caJobLayer::setCurrentScript(IPrjStatus *st)
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
        st->setNextExec("");
        switch(st->getMainPhase())
        {
        case ST_COMPLETE:
        case ST_NONE:
            break;
        case ST_SOURCE:
            st->setNextExec(source_script_name[st->getPhaseSource()]);
            break;
        case ST_BUILD:
            st->setNextExec(build_script_name[st->getPhaseBuild()]);
            break;
        case ST_PACKAGE:
            st->setNextExec(package_script_name[st->getPhasePackage()]);
            break;
        case ST_DEPLOY:
            st->setNextExec(deploy_script_name[st->getPhaseDeploy()]);
            break;
        }
    }
}

void caJobLayer::setNextStep(IPrjStatus *st)
{
    if (st)
    {
        switch(st->getMainPhase())
        {
        case ST_COMPLETE:
            break;
        case ST_NONE:
            st->clearAllStatus();
            st->setMainPhase(ST_SOURCE);
            break;
        case ST_SOURCE:
            if(st->getPhaseSource()==ST_SOURCE_POST_SAVE)
            {
                st->setMainPhase(ST_BUILD);
            }
            else
            {
                st->incPhaseSource();
            }
            break;
        case ST_BUILD:
            if(st->getPhaseBuild()==ST_BUILD_POST_INSTALL)
            {
                st->setMainPhase(ST_PACKAGE);
            }
            else
            {
                st->incPhaseBuild();
            }
            break;
        case ST_PACKAGE:
            if(st->getPhasePackage()==ST_PACKAGE_POST)
            {
                st->setMainPhase(ST_DEPLOY);
            }
            else
            {
                st->incPhasePackage();
            }
            break;
        case ST_DEPLOY:
            if(st->getPhaseDeploy()==ST_DEPLOY_POST)
            {
                st->setMainPhase(ST_COMPLETE);
            }
            else
            {
                st->incPhaseDeploy();
            }
            break;
        }
    }
}


}