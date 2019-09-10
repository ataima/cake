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


void caScheduler::addExec(IPrjStatus *work)
{
    auto test=works_set.find(work->getName());
    if(test==works_set.end())
    {
        works.push(work);
        LogInfo("%s : add work n. %d",work->getName().c_str(),works.size());
    }
    else
    {
        LogWarning("%s : work already present on to do works",work->getName().c_str());
    }
}

int caScheduler::doExec()
{
    return 0;
}

caSchedulerManager::caSchedulerManager(size_t max_task)
{
    auto v=ST_NONE;
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
    auto res=0;
    IScheduler *exec=workers.at(ST_SOURCE);
    if(exec!=nullptr)
    {
        res=exec->doExec();
    }
    if(res==0)
    {
        exec=workers.at(ST_BUILD);
        if(exec!=nullptr)
        {
            res=exec->doExec();
        }
        if(res==0)
        {
            exec=workers.at(ST_PACKAGE);
            if(exec!=nullptr)
            {
                res=exec->doExec();
            }
            if(res==0)
            {
                exec=workers.at(ST_DEPLOY);
                if(exec!=nullptr)
                {
                    res=exec->doExec();
                }
            }
        }
    }
    return res;
}

}