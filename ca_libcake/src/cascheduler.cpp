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
#include "caprjstatus.h"
#include <unistd.h>

namespace CA
{

ISchedulerManager *ISchedulerManager::instance=nullptr;

ISchedulerManager * ISchedulerManager::getInstance(void)
{
    return instance;
}

void  ISchedulerManager::setInstance(ISchedulerManager *_mng)
{
    instance=_mng;
}


caScheduler::caScheduler(phaseMaxTask & _max_thread,prjPhase _phase):phase(_phase)
{
    max_thread=caPhaseUtils::getPhaseMaxThread(phase,_max_thread);
    thmanager=nullptr;
}


size_t caScheduler::appendJobs(IScheduler *prevJobs)
{
    auto res=0;
    if(prevJobs)
    {
        prjStatusArray & wh=prevJobs->getCurrentWorks();
        auto wit=wh.begin();
        auto wend=wh.end();
        while(wit!=wend)
        {
            if((*wit)->getMainPhase()==phase)
            {
                works.push_back(*wit);
                wit=wh.erase(wit);
                res++;
            }
            else
                wit++;
        }
    }
    return res;
}


size_t caScheduler::removeCompleted(void)
{
    auto res=0;
    auto wit=works.begin();
    auto wend=works.end();
    while(!works.empty())
    {
        if((*wit)->getMainPhase()==ST_COMPLETE)
        {
            wit=works.erase(wit);
            res++;
        }
        else
            wit++;
    }
    return res;
}

void caScheduler::addExec(IPrjStatus *work)
{
    auto test=works_set.find(work->getName());
    if(test==works_set.end())
    {
        works.push_back(work);
        works_set.insert(work->getName());
        LogInfo("%s : add work n. %d",work->getName().c_str(),works.size());
    }
    else
    {
        LogWarning("%s : work already present on to do works",work->getName().c_str());
    }
}


void * caScheduler::shellfunc(void * param)
{
    auto res=-1;
    int *res_ptr=nullptr;
    caPrjStatus * thst=static_cast<caPrjStatus *>(param);
    if(thst!=nullptr)
    {
        std::string script=thst->getPathScript();
        caUtils::appendPath(script,thst->getNextExec());

        res=system(script.c_str());
        if(res==0)
        {
            LogInfo("EXEC : '%s' : RES=%d",script.c_str(),res);
        }
        else
        {
            LogError("EXEC : '%s' : RES=%d",script.c_str(),res);
        }
        thst->setExecResult(res);
    }
    if(res)
        res_ptr++;
    return (void* )res_ptr;
}


int caScheduler::doExec()
{
    auto jresult=-1;
    LogInfo("SCHEDULER : PHASE : %s >> JOBS : %d : %d",caPhaseUtils::mainPhaseToCStr(phase),works_set.size(),max_thread);
    while(1)
    {
        thmanager= new caThreadManager();
        if(thmanager!=nullptr)
        {
            auto numtoexec=0;
            auto numthisphase=0;
            for(auto w : works )
            {
                caPrjStatus * wst=dynamic_cast<caPrjStatus *>(w);
                if(wst!=nullptr &&  wst->getMainPhase()==phase)
                {
                    thmanager->AddClient(shellfunc,wst,numtoexec,wst->getName().c_str());
                    numtoexec++;
                }
            }
            if(numtoexec>0)
            {
                thmanager->StartClients(max_thread);
                statusThreads st;
                do
                {
                    thmanager->GetStatus(st);
                    usleep(10000);
                }
                while(st.clients>st.running);
                thmanager->GetStatus(st);
                LogInfo("SCHEDULER : PHASE : %s >> JOBS : %d  STARTED ",caPhaseUtils::mainPhaseToCStr(phase),works_set.size());
                do
                {
                    thmanager->GetStatus(st);
                    usleep(10000);
                }
                while(st.running>st.stopped);
                LogInfo("SCHEDULER : PHASE : %s >> JOBS : %d  COMPLETED ",caPhaseUtils::mainPhaseToCStr(phase),works_set.size());
                thmanager->GetStatus(st);
                jresult=st.errors;
                if(st.errors!=0)
                {
                    LogError("SCHEDULER : PHASE : %s >> JOB :  return ERRORS",caPhaseUtils::mainPhaseToCStr(phase));
                }
                // check IPrjStatus -> advance all OK
                LogInfo("SCHEDULER : PHASE : %s >> JOBS : UPDATE STATUS  ",caPhaseUtils::mainPhaseToCStr(phase));
                auto wit=works.begin();
                auto wend=works.end();
                while (wit!=wend)
                {
                    if((*wit)!=nullptr && (*wit)->getMainPhase()==phase && (*wit)->getExecResult()==0)
                    {
                        caPrjStatusUtils::save(*wit);
                        caPrjStatusUtils::setNextStep(*wit);
                        numthisphase++;
                    }
                    wit++;
                }
            }
            // end
            delete thmanager;
            thmanager=nullptr;
            // errors preset
            if(jresult!=0)break;
            // no more job in this phase
            if(numthisphase==0)break;
        }
    }
    return jresult;
}


caSchedulerManager::caSchedulerManager(phaseMaxTask &  max_thread)
{
    auto v=ST_NONE;
    memcpy(&max_task,&max_thread,sizeof(phaseMaxTask));
    workers.insert(workers.begin(),ST_COMPLETE,nullptr);
    for(v=ST_NONE; v<=ST_COMPLETE;)
    {
        switch(v)
        {
        case ST_NONE:
        case ST_COMPLETE:
            workers[(size_t)(v)]=nullptr;
            break;
        default:
            workers[(size_t)(v)]=new caScheduler(max_task,v);
            break;
        }
        size_t vv=(size_t)(v);
        v=(prjPhase)++vv;
    }
    ISchedulerManager::setInstance(this);
}


bool caSchedulerManager::doExec()
{
    class exec_phase
    {
    public:
        static int run(IScheduler * exec,IScheduler *next_exec )
        {
            auto res=exec->doExec();
            if( res==0 )
            {
                if ( next_exec!=nullptr )
                {
                    unsigned int execPh=(unsigned int)exec->getPhase();
                    unsigned int nextPh=(unsigned int)next_exec->getPhase();
                    if(execPh<nextPh)
                    {
                        next_exec->appendJobs(exec);
                    }
                }
                else
                {
                    unsigned int execPh=(unsigned int)exec->getPhase();
                    if(execPh==ST_DEPLOY)
                    {
                        exec->removeCompleted();
                    }
                }
            }
            return res;
        }
    };

    auto res=0;
    IScheduler *exec=workers.at(ST_SOURCE);
    IScheduler *next_exec=workers.at(ST_BUILD);
    if(exec!=nullptr && !exec->empty())
    {
        do
        {
            res=exec_phase::run(exec,next_exec);
        }
        while(res==0 && !exec->empty());
    }
    if(res==0)
    {
        exec=workers.at(ST_BUILD);
        next_exec=workers.at(ST_PACKAGE);
        if(exec!=nullptr && !exec->empty())
        {
            do
            {
                res=exec_phase::run(exec,next_exec);
            }
            while(res==0 && !exec->empty());
        }
        if(res==0)
        {
            exec=workers.at(ST_PACKAGE);
            next_exec=workers.at(ST_PACKAGE);
            if(exec!=nullptr && !exec->empty())
            {
                do
                {
                    res=exec_phase::run(exec,next_exec);
                }
                while(res==0 && !exec->empty());
            }
            if(res==0)
            {
                exec=workers.at(ST_DEPLOY);
                next_exec=nullptr;
                if(exec!=nullptr && !exec->empty())
                {
                    do
                    {
                        res=exec_phase::run(exec,next_exec);
                    }
                    while(res==0 && !exec->empty());
                }
            }
        }
    }
    return res==0;
}


}