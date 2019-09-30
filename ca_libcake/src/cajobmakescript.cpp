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

bool caJobMakeBase::checkExistCustomScript(ICAjob_layer *layer ,IGetConfEnv  * env,
        IPrjStatus *pst,std::string & scriptToCreate)
{
    auto res=false;
    std::string confpath;
    caUtils::dirName (pst->getFullProjConf(),confpath) ;
    std::string script("scripts");
    caUtils::appendPath(confpath,script);
    caUtils::appendPath(confpath,pst->getNextExec());
    if(caUtils::checkFileExist(confpath))
    {
        std::ifstream fin(confpath);
        std::ofstream fout(scriptToCreate);
        if(fin.is_open() && fout.is_open())
        {
            fout<<fin.rdbuf();
            fout.flush();
            fin.close();
            fout.close();
            res=true;
        }
    }
    return res;
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
        // have to create or copy custom scripts
        if(caJobMakeBase::checkExistCustomScript(layer,env,pst,scriptToCreate)==false)
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
    }
    return res;
}

void caJobMakeBase::createScriptHeader(std::ofstream &of,IGetConfEnv  * env,envSet &subset)
{

    env->addEnvToScript(of,subset);
    of.flush();
    sync();
}




}


