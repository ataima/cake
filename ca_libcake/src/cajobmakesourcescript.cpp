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
#include "cajobmakescript.h"
#include "cajobstep.h"
#include "cajoblayer.h"
#include "cautils.h"
#include "castatusconf.h"
#include <caconfenv.h>
#include <cstdlib>
#include <sys/stat.h>
#include <unistd.h>
#include "capackedfile.h"


namespace CA
{


void caJobMakeSourceScript::create(ICAXml_Project *prj,ICAjob_layer *layer ,IGetConfEnv  * env, IPrjStatus *pst)
{
    funcCreateScript funcs[]=
    {
        nullptr,
        caJobMakeSourceScript::createPreDownload,
        caJobMakeSourceScript::createDownload,
        caJobMakeSourceScript::createPostDownload,
        caJobMakeSourceScript::createPrePatch,
        caJobMakeSourceScript::createPatch,
        caJobMakeSourceScript::createPostPatch,
        caJobMakeSourceScript::createPreSource,
        caJobMakeSourceScript::createSource,
        caJobMakeSourceScript::createPostSource,
        nullptr,
    };
    caJobMakeBase::createScriptPhase(prj,layer,env,pst,funcs,pst->getPhaseSource());
}




void caJobMakeSourceScript::createDefaultSourceHeader(std::ofstream & of,IGetConfEnv  * env,
        IPrjStatus *pst)
{
    of<<"#!/bin/sh  ";
    IOptionArgvManager *argvObj=IOptionArgvManager::getInstance();
    if (argvObj && argvObj->getOption(f_debug)->isSelect())
    {
        of<<" -x"<<std::endl<<std::endl;
        of<<"# Debug mode on "<<std::endl;
        of<<"export PS4='+(${BASH_SOURCE}:${LINENO}): ${FUNCNAME[0]}: $(echo;echo \"->>\")'"<<std::endl<<std::endl;
    }
    std::string sources;
    env->getValue("SOURCES",sources);
    caUtils::appendPath(sources,pst->getName());
    of<<"#path where stored sources files"<<std::endl;
    of<<"export SOURCE="<<sources<<std::endl<<std::endl;
    env->getValue("STORE",sources);
    caUtils::appendPath(sources,pst->getName());
    of<<"#path where stored cpy of sources files"<<std::endl;
    of<<"export STORE="<<sources<<std::endl<<std::endl;
    sources=pst->getPathLog();
    caUtils::appendPath(sources,pst->getNextExec());
    caUtils::changeExt(sources,"log");
    of<<"#log of this script file"<<std::endl;
    of<<"export LOG="<<sources<<std::endl<<std::endl;
    of<<"#name of proeject"<<std::endl;
    of<<"export PROJECT="<<pst->getName()<<std::endl<<std::endl;
    of<<"# RESULT of operation brek on ok "<<std::endl;
    of<<"export RESULT=0"<<std::endl<<std::endl;
    of<<"#this script"<<std::endl;
    of<<"export SCRIPTNAME="<<pst->getNextExec()<<std::endl<<std::endl;
}

bool caJobMakeSourceScript::createPreDownload(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {
        createDefaultSourceHeader(of,env,pst);

        of<<packManager::getFile_default_log_sh();
        of<<packManager::getFile_pre_download_sh();
        of.flush();
        of.close();
        sync();
        return caUtils::checkFileExist(scriptname);
    }
    return false;
}


bool caJobMakeSourceScript::createDownload(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {

        CAXml_Project *conf=dynamic_cast<CAXml_Project *>(prj);
        if(conf!=nullptr)
        {
            createDefaultSourceHeader(of,env,pst);
            of<<packManager::getFile_download_key_sign_sh();
            for (auto ptrR : conf->remote)
            {
                CAXml_Project_Remote * remote = dynamic_cast<CAXml_Project_Remote *>(ptrR);
                std::string extfile;
                caUtils::baseExt(remote->file,extfile);
                if(!extfile.empty())
                {
                    if(extfile.find("tar")!=std::string::npos ||
                            extfile.find("zip")!=std::string::npos)
                    {
                        of<<packManager::getFile_expand_to_sh();
                    }
                }
            }
            of<<packManager::getFile_default_log_sh();
            for (auto ptrR : conf->remote)
            {
                CAXml_Project_Remote * remote = dynamic_cast<CAXml_Project_Remote *>(ptrR);
                std::string method;
                std::string extfile;
                caUtils::toUpperAlpha(remote->method,method);
                if(!remote->url.empty())
                {
                    of<<"# Download request url"<<std::endl;
                    of<<"export URL="<<remote->url<<std::endl<<std::endl;
                }
                else
                {
                    std::string msg="Unknow remote url on conf file : "+ pst->getFullProjConf();
                    sys_throw(msg);
                }
                if(!remote->file.empty())
                {
                    of<<"# Download request file"<<std::endl;
                    of<<"export FILE="<<remote->file<<std::endl<<std::endl;
                }
                else
                {
                    std::string msg="Unknow remote file on conf file : "+ pst->getFullProjConf();
                    sys_throw(msg);
                }
                extfile.clear();
                caUtils::baseExt(remote->file,extfile);
                if(extfile.find("tar")!=std::string::npos)
                {
                    of<<"# for file expansion "<<std::endl;
                    of<<"export PACKEXT=tar"<<std::endl<<std::endl;
                }
                else if(extfile.find("zip")!=std::string::npos)
                {
                    of<<"# for file expansion "<<std::endl;
                    of<<"export PACKEXT=zip"<<std::endl<<std::endl;
                }
                CAXml_Project_Remote_Key keyValue=remote->key;
                if(!keyValue.url.empty() && !keyValue.file.empty())
                {
                    of<<"# key sign verification url"<<std::endl;
                    of<<"export KEYURL="<<keyValue.url<<"/"<<keyValue.file<<std::endl;
                    extfile.clear();
                    caUtils::baseRevExt(keyValue.file,extfile);
                    of<<"# key sign ext"<<std::endl;
                    of<<"export KEYEXT="<<extfile<<std::endl<<std::endl;
                }
                else
                {
                    of<<"# key sign verification url"<<std::endl;
                    of<<"export KEYURL=N"<<std::endl;
                    of<<"# key sign ext"<<std::endl;
                    of<<"export KEYEXT=N"<<std::endl<<std::endl;
                }
                if(method=="GIT")
                {
                    of<<"# Download request branch"<<std::endl;
                    of<<"export BRANCH="<<remote->branch<<std::endl<<std::endl;
                    of<<"# Download request branch"<<std::endl;
                    of<<"export COMMIT="<<remote->commit<<std::endl<<std::endl;
                    of<<packManager::getFile_download_git_sh()<<std::endl;
                }
                else if(method=="SVN")
                {
                    of<<"# Download request revision"<<std::endl;
                    of<<"export REVISION="<<remote->revision<<std::endl<<std::endl;
                    of<<packManager::getFile_download_svn_sh()<<std::endl;
                }
                else if(method=="WGET")
                {
                    of<<packManager::getFile_download_wget_sh()<<std::endl;
                }
                else if(method=="RSYNC")
                {
                    of<<packManager::getFile_download_rsync_sh()<<std::endl;
                }
                else if(method=="APT")
                {
                    of<<packManager::getFile_download_apt_sh()<<std::endl;
                }
                else
                {
                    std::string msg=method + " not allowed on conf file :"+ pst->getFullProjConf();
                    sys_throw(msg);
                }
            }
        }
        of.flush();
        of.close();
        sync();
        return caUtils::checkFileExist(scriptname);
    }
    return false;
}


bool caJobMakeSourceScript::createPostDownload(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {
        CAXml_Project *conf=dynamic_cast<CAXml_Project *>(prj);
        if(conf!=nullptr)
        {
            createDefaultSourceHeader(of,env,pst);
            of<<packManager::getFile_verify_store_backup_sh();
            of<<packManager::getFile_default_log_sh();
            for (auto ptrR : conf->remote)
            {
                CAXml_Project_Remote * remote = dynamic_cast<CAXml_Project_Remote *>(ptrR);
                std::string method;
                std::string extfile;
                caUtils::toUpperAlpha(remote->method,method);
                if(!remote->url.empty())
                {
                    of<<"# Download request url"<<std::endl;
                    of<<"export URL="<<remote->url<<std::endl<<std::endl;
                }
                else
                {
                    std::string msg="Unknow remote url on conf file : "+ pst->getFullProjConf();
                    sys_throw(msg);
                }
                if(!remote->file.empty())
                {
                    of<<"# Download request file"<<std::endl;
                    of<<"export FILE="<<remote->file<<std::endl<<std::endl;
                }
                else
                {
                    std::string msg="Unknow remote file on conf file : "+ pst->getFullProjConf();
                    sys_throw(msg);
                }
                extfile.clear();
                caUtils::baseExt(remote->file,extfile);
                if(extfile.find("tar")!=std::string::npos)
                {
                    of<<"# for file expansion "<<std::endl;
                    of<<"export PACKEXT=tar"<<std::endl<<std::endl;
                }
                else if(extfile.find("zip")!=std::string::npos)
                {
                    of<<"# for file expansion "<<std::endl;
                    of<<"export PACKEXT=zip"<<std::endl<<std::endl;
                }
                CAXml_Project_Remote_Key keyValue=remote->key;
                if(!keyValue.url.empty() && !keyValue.file.empty())
                {
                    of<<"# key sign verification url"<<std::endl;
                    of<<"export KEYURL="<<keyValue.url<<"/"<<keyValue.file<<std::endl;
                    extfile.clear();
                    caUtils::baseRevExt(keyValue.file,extfile);
                    of<<"# key sign ext"<<std::endl;
                    of<<"export KEYEXT="<<extfile<<std::endl<<std::endl;
                }
                else
                {
                    of<<"# key sign verification url"<<std::endl;
                    of<<"export KEYURL=N"<<std::endl;
                    of<<"# key sign ext"<<std::endl;
                    of<<"export KEYEXT=N"<<std::endl<<std::endl;
                }
                if(method=="GIT")
                {
                    of<<"# Download request branch"<<std::endl;
                    of<<"export BRANCH="<<remote->branch<<std::endl<<std::endl;
                    of<<"# Download request branch"<<std::endl;
                    of<<"export COMMIT="<<remote->commit<<std::endl<<std::endl;
                    of<<packManager::getFile_post_download_git_sh()<<std::endl;
                }
                else if(method=="SVN")
                {
                    of<<"# Download request revision"<<std::endl;
                    of<<"export REVISION="<<remote->revision<<std::endl<<std::endl;
                    of<<packManager::getFile_post_download_svn_sh()<<std::endl;
                }
                else if(method=="WGET")
                {
                    of<<packManager::getFile_post_download_wget_sh()<<std::endl;
                }
                else if(method=="RSYNC")
                {
                    of<<packManager::getFile_post_download_rsync_sh()<<std::endl;
                }
                else if(method=="APT")
                {
                    of<<packManager::getFile_post_download_apt_sh()<<std::endl;
                }
                else
                {
                    std::string msg=method + " not allowed on conf file :"+ pst->getFullProjConf();
                    sys_throw(msg);
                }
            }
        }
        of.flush();
        of.close();
        sync();
        return caUtils::checkFileExist(scriptname);
    }
    return false;
}

bool caJobMakeSourceScript::createPrePatch(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {
        envSet subset;
        caJobMakeBase::createScriptHeader(of,env,subset);
    }
    of.close();
    return caUtils::checkFileExist(scriptname);
}


bool caJobMakeSourceScript::createPatch(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {
        envSet subset;
        caJobMakeBase::createScriptHeader(of,env,subset);
    }
    of.close();
    return caUtils::checkFileExist(scriptname);
}


bool caJobMakeSourceScript::createPostPatch(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {
        envSet subset;
        caJobMakeBase::createScriptHeader(of,env,subset);
    }
    of.close();
    return caUtils::checkFileExist(scriptname);
}


bool caJobMakeSourceScript::createPreSource(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {
        envSet subset;
        caJobMakeBase::createScriptHeader(of,env,subset);
    }
    of.close();
    return caUtils::checkFileExist(scriptname);
}


bool caJobMakeSourceScript::createSource(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {
        envSet subset;
        caJobMakeBase::createScriptHeader(of,env,subset);
    }
    of.close();
    return caUtils::checkFileExist(scriptname);
}


bool caJobMakeSourceScript::createPostSource(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {
        envSet subset;
        caJobMakeBase::createScriptHeader(of,env,subset);
    }
    of.close();
    return caUtils::checkFileExist(scriptname);
}

}
