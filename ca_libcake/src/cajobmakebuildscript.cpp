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



void caJobMakeBuildScript::create(ICAXml_Project *prj,ICAjob_layer *layer ,IGetConfEnv  * env, IPrjStatus *pst)
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
    caJobMakeBase::createScriptPhase(prj,layer,env,pst,funcs,pst->getPhaseBuild());
}

bool caJobMakeBuildScript::createPreConfigure(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
{
    std::ofstream of(scriptname);
    if(of.is_open())
    {
        envSet subset;
        caJobMakeBase::createScriptHeader(of,env,subset);
    }
    of.close();
    return caUtils::checkFileExist(scriptname);;
}


bool caJobMakeBuildScript::createConfigure(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
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


bool caJobMakeBuildScript::createPostConfigure(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
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


bool caJobMakeBuildScript::createPreBuild(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
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


bool caJobMakeBuildScript::createBuild(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
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


bool caJobMakeBuildScript::createPostBuild(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
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


bool caJobMakeBuildScript::createPreInstall(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
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


bool caJobMakeBuildScript::createInstall(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
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


bool caJobMakeBuildScript::createPostInstall(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname)
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


