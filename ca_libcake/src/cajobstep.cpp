
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
#include "calogger.h"
#include "cacakemanager.h"
#include "calayerconf.h"
#include "caprojectconf.h"
#include "cajobstep.h"
#include "cajoblayer.h"
#include "cajobmakescript.h"
#include "cautils.h"
#include <caconfenv.h>
#include <cstdlib>
#include "cascheduler.h"
#include "caphaseutils.h"

namespace CA
{



void caJobStep::AddUserEnv(void)
{
    CAXml_Main_Defaults_Step *step=dynamic_cast<CAXml_Main_Defaults_Step*>(step_conf);
    if(!step->user_env.empty())
    {
        for(auto tmp : step->user_env)
        {
            CAXml_Main_Defaults_Step_User_env *uenv= dynamic_cast<CAXml_Main_Defaults_Step_User_env*>(tmp);
            if(uenv)
            {
                env->add(uenv->name.c_str(),uenv->value);
            }
        }
    }
}



caJobStep::caJobStep(ICAXml_Main_Defaults_Step  *_step_conf,ICAXml_Layer *_layers_conf)
    :step_conf(_step_conf),layers_conf(_layers_conf),env(nullptr)
{
    layer= new caJobLayer(this);
}

caJobStep::~caJobStep()
{
    reset();
}

void  caJobStep::reset(void)
{
    delete layers_conf;
    layers_conf=nullptr;
    delete env;
    env=nullptr;
    delete layer;
    layer=nullptr;
}

void caJobStep::prepareDefaultEnv(IGetConfEnv  * _env)
{
    env=new caGetConfEnv(_env);
    if(step_conf)
    {
        envMap tmp;
        CAXml_Main_Defaults_Step *step=dynamic_cast<CAXml_Main_Defaults_Step*>(step_conf);
        step->toMap(tmp,true);
        if(!tmp.empty())
            env->add(tmp);
        auto usr_env=env->getMap().find("USER_ENV");
        if(usr_env!=env->getMap().end())
        {
            env->getMap().erase(usr_env);
        }
        AddUserEnv();
        std::string logdir;
        env->getValue("LOGS",logdir);
        std::string logfile=logdir;
        caUtils::appendPath(logfile,step->name);
        logfile+="_"+step->id+"_env.log";
        FilePrinter printer (logfile.c_str());
        CA::ILogger::getInstance()->addOutput(&printer);
        std::string msg="Step "+step->name+" configuration";
        env->dump(msg.c_str());
        CA::ILogger::getInstance()->sync();
        CA::ILogger::getInstance()->removeOutput(&printer);
    }
}


void caJobStep::doPrepare(void)
{
    layer->prepareScripts();
}


bool caJobStep::doWork(void)
{
    auto res=false;
    std::list<std::string> order_prj;
    auto towork=layer->getNumWork(order_prj);
    if(towork>0)
    {
        statusMap *st=layer->getStatusMap();
        if(!st->empty())
        {
            prepareScheduler();
            ISchedulerManager * msched=ISchedulerManager::getInstance();
            for(auto prj: order_prj)
            {
                auto it=st->find(prj);
                if(it!=st->end())
                {
                    if(it->second->getMainPhase()!=ST_COMPLETE)
                    {
                        if(msched!=nullptr)
                        {
                            msched->addExec(it->second);
                        }
                    }
                }
            }
            res=msched->doExec();
        }
    }
    else
    {
        CAXml_Main_Defaults_Step *step=dynamic_cast<CAXml_Main_Defaults_Step *>(step_conf);
        LogInfo("%s : %s : COMPLETE !",step->name.c_str(),layer->getName().c_str());
    }
    return res;
}

void caJobStep::prepareScheduler()
{
// to do add policy scheduler and instantiate a specific scheduler ...
    phaseMaxTask maxtask;
    caPhaseUtils::setMaxTask(layers_conf,maxtask);
    caSchedulerManager *manager= new caSchedulerManager(maxtask);
}


//////////////////////////////////////////////////////////////////////////////////
void caJobStepManager::reset()
{
    for (auto job : *this)
    {
        job->reset();
        delete job;
    }
    clear();
}

void caJobStepManager::prepareStep(IGetConfEnv  * _env)
{
    for(auto job: *this)
    {
        if(job)
        {
            job->prepareDefaultEnv(_env);
        }
    }

}


bool caJobStepManager::doWork(void)
{
    auto res=false;
    for(auto job: *this)
    {
        if(job)
        {
            res=job->doWork();
        }
        if(res==false)
            break;
    }
    return res;
}

void caJobStepManager::doPrepare(void)
{
    for(auto job: *this)
    {
        if(job)
        {
            job->doPrepare();
        }
    }
}


}