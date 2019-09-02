
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
    auto * step= dynamic_cast<CAXml_Main_Defaults_Step *>(jobstep->getStep());
    caUtils::getFileName(step->layer,layer_name);
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
        if(!caUtils::compareChangeDate(projconf,p_status))
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
                it->second->st->loadFromXml(p_status);
            }
            else
            {
                LogInfo("%s:Loading  project %s status ",layer_name.c_str(),prj.c_str());
                ICAXml_Status *status =new CAXml_Status();
                status->loadFromXml(p_status);
                auto *ns=new prjStatus;
                ns->name=prj;
                ns->fullpath=p_status;
                ns->fullprojconf=projconf;
                ns->st=status;
                std::pair<std::string,prjStatus *> pv(prj,ns);
                projects_status.insert(pv);
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
            auto *ns=new prjStatus;
            ns->name=prj;
            ns->fullpath=p_status;
            ns->fullprojconf=projconf;
            ns->st=status;
            std::pair<std::string,prjStatus *> ps(prj,ns);
            projects_status.insert(ps);
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
        st->next_exec = "none";
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
                st->next_exec="pre_download.sh";
                st->phase=ST_SOURCE;
                st->pSource=ST_SOURCE_PRE_DOWNLOAD;
            }
            else if(cur->download!="1")
            {
                st->next_exec="download.sh";
                st->phase=ST_SOURCE;
                st->pSource=ST_SOURCE_DOWNLOAD;
            }
            else if(cur->post_download!="1")
            {
                st->next_exec="post_download.sh";
                st->phase=ST_SOURCE;
                st->pSource=ST_SOURCE_POST_DOWNLOAD;
            }
            else if(cur->pre_patch!="1")
            {
                st->next_exec="pre_patch.sh";
                st->phase=ST_SOURCE;
                st->pSource=ST_SOURCE_PRE_PATCH;
            }
            else if(cur->patch!="1")
            {
                st->next_exec="patch.sh";
                st->phase=ST_SOURCE;
                st->pSource=ST_SOURCE_PATCH;
            }
            else if(cur->post_patch!="1")
            {
                st->next_exec="post_patch.sh";
                st->phase=ST_SOURCE;
                st->pSource=ST_SOURCE_POST_PATCH;
            }
            else if(cur->pre_save_source!="1")
            {
                st->next_exec="pre_save_source.sh";
                st->phase=ST_SOURCE;
                st->pSource=ST_SOURCE_PRE_SAVE;
            }
            else if(cur->save_source!="1")
            {
                st->next_exec="save_source.sh";
                st->phase=ST_SOURCE;
                st->pSource=ST_SOURCE_SAVE;
            }
            else if(cur->post_save_source!="1")
            {
                st->next_exec="post_save_source.sh";
                st->phase=ST_SOURCE;
                st->pSource=ST_SOURCE_POST_SAVE;
            }
            else if(cur->pre_configure!="1")
            {
                st->next_exec="pre_configure.sh";
                st->phase=ST_BUILD;
                st->pBuild=ST_BUILD_PRE_CONFIGURE;
            }
            else if(cur->configure!="1")
            {
                st->next_exec="configure.sh";
                st->phase=ST_BUILD;
                st->pBuild=ST_BUILD_CONFIGURE;
            }
            else if(cur->post_configure!="1")
            {
                st->next_exec="post_configure.sh";
                st->phase=ST_BUILD;
                st->pBuild=ST_BUILD_POST_CONFIGURE;
            }
            else if(cur->pre_build!="1")
            {
                st->next_exec="pre_build.sh";
                st->phase=ST_BUILD;
                st->pBuild=ST_BUILD_PRE_BUILD;
            }
            else if(cur->build!="1")
            {
                st->next_exec="build.sh";
                st->phase=ST_BUILD;
                st->pBuild=ST_BUILD_BUILD;
            }
            else if(cur->post_build!="1")
            {
                st->next_exec="post_build.sh";
                st->phase=ST_BUILD;
                st->pBuild=ST_BUILD_POST_BUILD;
            }
            else if(cur->pre_install!="1")
            {
                st->next_exec="pre_install.sh";
                st->phase=ST_BUILD;
                st->pBuild=ST_BUILD_PRE_INSTALL;
            }
            else if(cur->install!="1")
            {
                st->next_exec="install.sh";
                st->phase=ST_BUILD;
                st->pBuild=ST_BUILD_INSTALL;
            }
            else if(cur->post_install!="1")
            {
                st->next_exec="post_install.sh";
                st->phase=ST_BUILD;
                st->pBuild=ST_BUILD_POST_INSTALL;
            }
            else if(cur->pre_package!="1")
            {
                st->next_exec="pre_package.sh";
                st->phase=ST_PACKAGE;
                st->pPackage=ST_PACKAGE_PRE;
            }
            else if(cur->package!="1")
            {
                st->next_exec="package.sh";
                st->phase=ST_PACKAGE;
                st->pPackage=ST_PACKAGE_PACKAGE;
            }
            else if(cur->post_package!="1")
            {
                st->next_exec="post_package.sh";
                st->phase=ST_PACKAGE;
                st->pPackage=ST_PACKAGE_POST;
            }
            else if(cur->pre_deploy!="1")
            {
                st->next_exec="pre_deploy.sh";
                st->phase=ST_DEPLOY;
                st->pDeploy=ST_DEPLOY_PRE;
            }
            else if(cur->deploy!="1")
            {
                st->next_exec="deploy.sh";
                st->phase=ST_DEPLOY;
                st->pDeploy=ST_DEPLOY_IMAGE;
            }
            else if(cur->post_deploy!="1")
            {
                st->next_exec="post_deploy.sh";
                st->phase=ST_DEPLOY;
                st->pDeploy=ST_DEPLOY_POST;
            }
            else
            {
                st->next_exec="done";
                st->phase=ST_COMPLETE;
            }
        }
    }
}




}