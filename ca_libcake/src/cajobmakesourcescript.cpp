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
        of<<"#!/bin/sh  ";
        IOptionArgvManager *argvObj=IOptionArgvManager::getInstance();
        if (argvObj && argvObj->getOption(f_debug)->isSelect())
        {
            of<<" -x";
        }
        of<<std::endl;
        std::string sources;
        env->getValue("SOURCES",sources);
        caUtils::appendPath(sources,pst->getName());
        of<<"#path where stored sources files"<<std::endl;
        of<<"export SOURCE="<<sources<<std::endl<<std::endl;
        sources="";
        env->getValue("LOGS",sources);
        std::string logname=sources;
        sources=pst->getLayer()+"_"+pst->getName()+"_pre_download.log";
        caUtils::appendPath(logname,sources);
        of<<"#log of this script file"<<std::endl;
        of<<"export LOG="<<logname<<std::endl<<std::endl;
    }
    unsigned int len;
    const char * script=packManager::getFile_pre_download_sh(&len);
    of<<script;
    of.flush();
    of.close();
    sync();
    return caUtils::checkFileExist(scriptname);
}


bool caJobMakeSourceScript::createDownload(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
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


bool caJobMakeSourceScript::createPostDownload(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
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

bool caJobMakeSourceScript::createPrePatch(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
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


bool caJobMakeSourceScript::createPatch(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
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


bool caJobMakeSourceScript::createPostPatch(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
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


bool caJobMakeSourceScript::createPreSource(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
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


bool caJobMakeSourceScript::createSource(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
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


bool caJobMakeSourceScript::createPostSource(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
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
