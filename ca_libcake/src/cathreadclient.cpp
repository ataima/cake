
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

#include <stdio.h>
#include <thread>
#include <errno.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <cathreadclient.h>


namespace CA
{

caThreadClient::caThreadClient( int index,cleanctor cc)
{

    mStatus = STOPPED;
    mThid = nullptr;
    reqFunc = nullptr;
    reqParam = nullptr;
    mIndex = index;
    mTickCount = 0;
    mName[0] = '\0';
    cleanfunc=cc;
}

void caThreadClient::Reset()
{
    if(mThid!=nullptr)
        mThid->join();
    CreateThread();
}

caThreadClient::~caThreadClient()
{
    if(mThid!=nullptr)
        delete mThid;
}

bool caThreadClient::InitThread(functor func, void *param, const char *name)
{

    bool result ;
    reqFunc = func;
    reqParam = param;
    result = CreateThread();
    memcpy(mName, name, 31);
    return result;
}

bool caThreadClient::CreateThread()
{

    if(mThid!=nullptr)
        delete mThid;
    mThid=new std::thread(entry_point,this);
    return mThid==nullptr;
}


void caThreadClient::SleepThread(unsigned int delay)
{

    if (delay < 1000)
        usleep(delay * 1000);
    else
    {
        usleep((delay % 1000)*1000);
        sleep(delay / 1000);
    }
}

void * caThreadClient::entry_point(void *param)
{
    int * resptr=nullptr;
    size_t res = 0;
    auto client = static_cast<caThreadClient*> (param);
    if (client != nullptr)
    {
        client->WaitForSignal();
        res = client->ExecuteClient();
        client->setStatus(caThreadStatus::EXITED);
        client->finalize_cleanup(res);
#if MOREDEBUG
        std::cerr << "thread " << client->getName() << " EXITED!" << std::endl;
#endif
    }
    if(res)resptr++;
    return (void *)resptr;
}



void caThreadClient::CondWait()
{

    std::unique_lock<std::mutex> lck(mMtx);
    mCond.wait(lck);
}


void  caThreadClient::CondSignal()
{
    std::unique_lock<std::mutex> lck(mMtx);
    mCond.notify_one();
}



void caThreadClient::WaitForSignal()
{

    mStatus = WAIT_SIGNAL;
    CondWait();
    mTickCount++;
}



int caThreadClient::ExecuteClient()
{

    int res=-1;
    if (reqFunc != nullptr)
    {
        mStatus = RUNNING;
        if(reqFunc(reqParam)==nullptr)
            res=0;
    }
    return res;
}


void caThreadClient::Resume()
{

    CondSignal();
    mStatus = RESUME;
}


void caThreadClient::ReqExit()
{
    auto count=0;
    while(mStatus!=EXITED)
    {
        usleep(10000);
        count++;
        if(count>100)break;
    }
    if(mThid->joinable())
        mThid->join();
    mStatus = EXITED;
}


}