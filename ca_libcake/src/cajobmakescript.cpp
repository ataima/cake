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


namespace CA
{


bool caJobMakeBase::checkStatusScript(ICAjob_layer *layer ,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    auto res=false;
    std::string replaced;
    env->getValue("SCRIPTS",replaced);
    caUtils::appendPath(replaced,layer->getName());
    caUtils::checkDirExistOrCreate(replaced);
    caUtils::appendPath(replaced,pst->getName());
    caUtils::checkDirExistOrCreate(replaced);
    if(pst->getPathScript()!=replaced)
    {
        pst->setPathScript(replaced);
    }
    caUtils::appendPath(replaced,pst->getNextExec());
    scriptname=replaced;
    IOptionArgvManager *argvObj=IOptionArgvManager::getInstance();
    if (argvObj && argvObj->getOption(f_force_generate)->isSelect())
    {
        LogInfo("Layer : %s : Project : %s : scripts :\n\t -> %s  force generation",layer->getName().c_str(),pst->getName().c_str(),pst->getNextExec().c_str());
        remove(scriptname.c_str());
    }
    if(caUtils::checkFileExist(scriptname))
    {

        res=caUtils::compareFileChangeDate(pst->getFullProjConf(),scriptname);
        if( !res)
        {
            LogInfo("Layer : %s : Project : %s : scripts :\n\t -> %s out of date remove",layer->getName().c_str(),pst->getName().c_str(),pst->getNextExec().c_str());
            remove(scriptname.c_str());
        }
        else
        {
            LogInfo("Layer : %s : Project : %s : scripts :\n\t -> %s syncronized",layer->getName().c_str(),pst->getName().c_str(),pst->getNextExec().c_str());
        }
    }
    return res;
    /// false to create script file
}

bool caJobMakeBase::createScriptPhase(ICAjob_layer *layer ,IGetConfEnv  * env,
                                      IPrjStatus *pst,const funcCreateScript funcs[],size_t off)
{
    auto res=false;
    std::string scriptToCreate;
    if(funcs==nullptr)
    {
        std::string msg("Invalid function table");
        sys_throw(msg);
    }
    res=caJobMakeBase::checkStatusScript(layer,env,pst,scriptToCreate);
    if(!res)
    {
        funcCreateScript funcToCreate=funcs[off];
        if(funcToCreate!=nullptr)
        {
            res=funcToCreate(env,pst,scriptToCreate);
            if(res)
            {
                sync();
                chmod(scriptToCreate.c_str(),0775);
                LogInfo("Layer : %s : Project : %s :\n\t ->create script file %s",layer->getName().c_str(),pst->getName().c_str(),scriptToCreate.c_str());
            }
            else
            {
                LogError("Layer : %s : Project : %s :\n\t ->Fail to create script file %s",layer->getName().c_str(),pst->getName().c_str(),scriptToCreate.c_str());
            }
        }
    }
    return res;
}

void caJobMakeBase::createScriptHeader(std::ofstream &of,IGetConfEnv  * env)
{
    of<<"#!/bin/sh  ";
    IOptionArgvManager *argvObj=IOptionArgvManager::getInstance();
    if (argvObj && argvObj->getOption(f_debug)->isSelect())
    {
        of<<" -x";
    }
    of<<std::endl;
    env->addEnvToScript(of);
    //auto w=rand()&7;
    //of<<"sleep "<<w<<std::endl;
    of<<"exit 0 "<<std::endl;
    of.flush();
    sync();
}

void caJobMakeSourceScript::create(ICAjob_layer *layer ,IGetConfEnv  * env, IPrjStatus *pst)
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
    caJobMakeBase::createScriptPhase(layer,env,pst,funcs,pst->getPhaseSource());
}


bool caJobMakeSourceScript::createPreDownload(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {
        caJobMakeBase::createScriptHeader(of,env);
    }
    of.close();
    return caUtils::checkFileExist(scriptname);
}


bool caJobMakeSourceScript::createDownload(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {
        caJobMakeBase::createScriptHeader(of,env);
    }
    of.close();
    return caUtils::checkFileExist(scriptname);
}


bool caJobMakeSourceScript::createPostDownload(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {
        caJobMakeBase::createScriptHeader(of,env);
    }
    of.close();
    return caUtils::checkFileExist(scriptname);
}

bool caJobMakeSourceScript::createPrePatch(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {
        caJobMakeBase::createScriptHeader(of,env);
    }
    of.close();
    return caUtils::checkFileExist(scriptname);
}


bool caJobMakeSourceScript::createPatch(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {
        caJobMakeBase::createScriptHeader(of,env);
    }
    of.close();
    return caUtils::checkFileExist(scriptname);
}


bool caJobMakeSourceScript::createPostPatch(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {
        caJobMakeBase::createScriptHeader(of,env);
    }
    of.close();
    return caUtils::checkFileExist(scriptname);
}


bool caJobMakeSourceScript::createPreSource(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {
        caJobMakeBase::createScriptHeader(of,env);
    }
    of.close();
    return caUtils::checkFileExist(scriptname);
}


bool caJobMakeSourceScript::createSource(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {
        caJobMakeBase::createScriptHeader(of,env);
    }
    of.close();
    return caUtils::checkFileExist(scriptname);
}


bool caJobMakeSourceScript::createPostSource(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {
        caJobMakeBase::createScriptHeader(of,env);
    }
    of.close();
    return caUtils::checkFileExist(scriptname);
}

////////////////////////////////////////////////////////////////////////////


void caJobMakeBuildScript::create(ICAjob_layer *layer ,IGetConfEnv  * env, IPrjStatus *pst)
{
    funcCreateScript funcs[]=
    {
        nullptr,
        caJobMakeBuildScript::createPreConfigure,
        caJobMakeBuildScript::createConfigure,
        caJobMakeBuildScript::createPostConfigure,
        caJobMakeBuildScript::createPreBuild,
        caJobMakeBuildScript::createBuild,
        caJobMakeBuildScript::createPostBuild,
        caJobMakeBuildScript::createPreInstall,
        caJobMakeBuildScript::createInstall,
        caJobMakeBuildScript::createPostInstall,
        nullptr,
    };
    caJobMakeBase::createScriptPhase(layer,env,pst,funcs,pst->getPhaseBuild());
}

bool caJobMakeBuildScript::createPreConfigure(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {
        caJobMakeBase::createScriptHeader(of,env);
    }
    of.close();
    return caUtils::checkFileExist(scriptname);;
}


bool caJobMakeBuildScript::createConfigure(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {
        caJobMakeBase::createScriptHeader(of,env);
    }
    of.close();
    return caUtils::checkFileExist(scriptname);
}


bool caJobMakeBuildScript::createPostConfigure(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {
        caJobMakeBase::createScriptHeader(of,env);
    }
    of.close();
    return caUtils::checkFileExist(scriptname);
}


bool caJobMakeBuildScript::createPreBuild(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {
        caJobMakeBase::createScriptHeader(of,env);
    }
    of.close();
    return caUtils::checkFileExist(scriptname);
}


bool caJobMakeBuildScript::createBuild(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {
        caJobMakeBase::createScriptHeader(of,env);
    }
    of.close();
    return caUtils::checkFileExist(scriptname);
}


bool caJobMakeBuildScript::createPostBuild(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {
        caJobMakeBase::createScriptHeader(of,env);
    }
    of.close();
    return caUtils::checkFileExist(scriptname);
}


bool caJobMakeBuildScript::createPreInstall(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {
        caJobMakeBase::createScriptHeader(of,env);
    }
    of.close();
    return caUtils::checkFileExist(scriptname);
}


bool caJobMakeBuildScript::createInstall(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {
        caJobMakeBase::createScriptHeader(of,env);
    }
    of.close();
    return caUtils::checkFileExist(scriptname);
}


bool caJobMakeBuildScript::createPostInstall(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {
        caJobMakeBase::createScriptHeader(of,env);
    }
    of.close();
    return caUtils::checkFileExist(scriptname);
}



//////////////////////////////////////////////////////////////////////////////


void caJobMakePackageScript::create(ICAjob_layer *layer ,IGetConfEnv  * env, IPrjStatus *pst)
{

    funcCreateScript funcs[]=
    {
        nullptr,
        caJobMakePackageScript::createPrePackage,
        caJobMakePackageScript::createPackage,
        caJobMakePackageScript::createPostPackage,
        nullptr,
    };
    caJobMakeBase::createScriptPhase(layer,env,pst,funcs,pst->getPhasePackage());
}



bool        caJobMakePackageScript::createPrePackage(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {
        caJobMakeBase::createScriptHeader(of,env);
    }
    of.close();
    return caUtils::checkFileExist(scriptname);
}


bool        caJobMakePackageScript::createPackage(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {
        caJobMakeBase::createScriptHeader(of,env);
    }
    of.close();
    return caUtils::checkFileExist(scriptname);
}


bool        caJobMakePackageScript::createPostPackage(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {
        caJobMakeBase::createScriptHeader(of,env);
    }
    of.close();
    return caUtils::checkFileExist(scriptname);
}



/////////////////////////////////////////////////////////////////////

void caJobMakeDeployScript::create(ICAjob_layer *layer ,IGetConfEnv  * env, IPrjStatus *pst)
{
    funcCreateScript funcs[]=
    {
        nullptr,
        caJobMakeDeployScript::createPreDeploy,
        caJobMakeDeployScript::createImage,
        caJobMakeDeployScript::createPostDeploy,
        nullptr,
    };
    caJobMakeBase::createScriptPhase(layer,env,pst,funcs,pst->getPhaseDeploy());
}

bool caJobMakeDeployScript::createPreDeploy(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {
        caJobMakeBase::createScriptHeader(of,env);
    }
    of.close();
    return caUtils::checkFileExist(scriptname);
}


bool caJobMakeDeployScript::createImage(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {
        caJobMakeBase::createScriptHeader(of,env);
    }
    of.close();
    return caUtils::checkFileExist(scriptname);
}


bool caJobMakeDeployScript::createPostDeploy(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {
        caJobMakeBase::createScriptHeader(of,env);
    }
    of.close();
    return caUtils::checkFileExist(scriptname);
}


}


