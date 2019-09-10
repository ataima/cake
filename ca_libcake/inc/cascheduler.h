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
#include <stack>

namespace CA
{




class caScheduler
    :public IScheduler
{
    std::stack<IPrjStatus *> works;
    std::set<std::string> works_set;
    size_t max_thread;
    prjPhase phase;
public:
    caScheduler (size_t _max_thread,prjPhase _phase):
        max_thread(_max_thread),phase(_phase) {}
    virtual void addExec( IPrjStatus * status) final;
    virtual int doExec() final;
};


class caSchedulerManager
    : public ISchedulerManager
{
    std::vector<IScheduler * > workers;
public:
    caSchedulerManager(size_t max_thread);
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