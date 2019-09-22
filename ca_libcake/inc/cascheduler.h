#ifndef CA_ARGV_FILE_HEADER
#define CA_ARGV_FILE_HEADER


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
#include "cajoblayer.h"
#include "caithread.h"
#include "cathreadclient.h"
#include "cathreadmanager.h"
#include <stack>

namespace CA
{







class caScheduler
    :public IScheduler
{
    prjStatusArray works;
    std::set<std::string> works_set;
    size_t max_thread;
    prjPhase phase;
    caThreadManager *thmanager;
public:
    virtual inline prjStatusArray & getCurrentWorks(void)final {return works;}
public:
    caScheduler (phaseMaxTask & _max_thread,prjPhase _phase);
    virtual size_t appendJobs(IScheduler *prevJobs)final;
    virtual size_t removeCompleted(void)final;
    virtual void addExec( IPrjStatus * status) final;
    virtual int doExec() final;
    virtual inline bool empty() final { return works.empty(); }
    virtual inline prjPhase getPhase()final{return phase;}
public:
    static void * shellfunc(void *param);
};


class caSchedulerManager
    : public ISchedulerManager
{
    phaseMaxTask max_task;
    std::vector<IScheduler * > workers;
public:
    caSchedulerManager(phaseMaxTask & max_thread);
    inline void addExec(IPrjStatus *status) final
    {
        IScheduler *exec=workers.at(status->getMainPhase());
        if(exec!=nullptr)
        {
            exec->addExec(status);
        }
    }
    bool doExec()final;
};

}

#endif