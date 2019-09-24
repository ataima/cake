
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
#include <pthread.h>
#include <caithread.h>
#include <cathreadclient.h>
#include <cathreadmanager.h>
#include <errno.h>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <set>

namespace CA
{

caThreadManager *caThreadManager::instance = nullptr;

caThreadManager::caThreadManager()
{
    HERE1();
    max_running=1;
    clients.clear();
    running.clear();
    stopped.clear();
    if (instance != nullptr)
    {
        std::cerr << "caThreadManager::instance already set !!" << std::endl;
    }
    errors=0;
    mMtxClients = PTHREAD_MUTEX_INITIALIZER;
    mMtxRun = PTHREAD_MUTEX_INITIALIZER;
    mMtxStop = PTHREAD_MUTEX_INITIALIZER;
    mMtxEnd = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_init(&mMtxClients,nullptr);
    pthread_mutex_init(&mMtxRun,nullptr);
    pthread_mutex_init(&mMtxStop,nullptr);
    pthread_mutex_init(&mMtxEnd,nullptr);
    pthread_cond_init(&mCond, NULL);
    instance = this;
}

caThreadManager::~caThreadManager()
{
    HERE1();
    auto err=0;
    StopClients();
    lockClients();
    for(auto th: clients)
    {
        err=0;
        while(th->getStatus()!=EXITED && err<1000)
        {
            usleep(10000);
            err++;
        }
        delete th;
    }
    clients.clear();
    errors=0;
    unlockClients();
    lockRunning();
    running.clear();
    unlockRunning();
    lockStopped();
    stopped.clear();
    unlockStopped();
    pthread_mutex_destroy(&mMtxClients);
    pthread_mutex_destroy(&mMtxRun);
    pthread_mutex_destroy(&mMtxStop);
    pthread_mutex_destroy(&mMtxEnd);
    pthread_cond_destroy(&mCond);
    instance = nullptr;
}

bool caThreadManager::AddClient(functor func, void *param,  size_t index, const char *name)
{
    HERE1();
    bool result = true;
    caThreadClient *client = new caThreadClient(index,caThreadManager::finalize_client);
    if (client != nullptr)
    {
        lockClients();
        clients.push_back(client);
        unlockClients();
        client->InitThread(func, param, name);
        while (client->getStatus() != caThreadStatus::WAIT_SIGNAL)
        {
            usleep(100);
        }
        result = false;
    }
    return result;
}

bool caThreadManager::Run(size_t index)
{
    HERE1();
    bool result = false;
    caThreadClient * clientThread =nullptr;
    //auto num_clients=GetClientsSize();
    //auto num_running=GetRunningSize();
    //if(num_running<num_clients)
    //{
    lockClients();
    clientThread = clients.at(index);
    unlockClients();
    lockRunning();
    running.push_back(clientThread);
    unlockRunning();
    //}
    if(clientThread!=nullptr &&  clientThread->getStatus() == caThreadStatus::WAIT_SIGNAL )
    {
        clientThread->Resume();
        result=true;
    }
    return result;
}

void  caThreadManager::finalize_client(size_t index,int error)
{
    caThreadManager *manager=caThreadManager::getInstance();
    if(manager!=nullptr)
    {
        manager->finalize(index,error);
    }
}

void  caThreadManager::finalize( size_t index, int result)
{
    caThreadClient * clientThread =nullptr;
    // save error
    // save to stopped thread
    lockRunning();
    if(result!=0)
    {
        errors++;
    }
    if(index<running.size())
        clientThread =running.at(index);
    unlockRunning();
    if(clientThread!=nullptr)
    {
        lockStopped();
        stopped.push_back(clientThread);
        unlockStopped();
    }
    //std::cerr<<"FINALIZE CLIENT = "<<index<<" "<<stopped.size()<<":"<<running.size()<<std::endl;
    // check more thread
    auto crun=GetRunningSize();
    auto cclient=GetClientsSize();
    auto cstop=GetStoppedSize();
    if(crun<cclient)
    {
        Run(crun);
    }
    if(cstop==cclient)
    {
        ClientsTerminateSignal();
    }
}


void caThreadManager::StopClients(void)
{
    lockRunning();
    thArray::iterator it = running.begin();
    thArray::iterator _end = running.end();
    while (it != _end)
    {
        if (*it != nullptr)
        {
            if((*it)->getStatus()!=EXITED)
                (*it)->ReqExit();
            *it = nullptr;
        }
        it++;
    }
    unlockRunning();
}


bool caThreadManager::Reset(void)
{
    auto res=false;
    statusThreads st;
    GetStatus(st);
    if(st.running==st.clients && st.stopped==st.clients)
    {
        lockClients();
        lockRunning();
        lockStopped();
        running.clear();
        errors=0;
        stopped.clear();
        for(auto th: clients)
        {
            th->Reset();
        }
        unlockStopped();
        unlockRunning();
        unlockClients();
        res=true;
    }
    return res;
}


size_t caThreadManager::GetClientsSize(void)
{
    HERE1();
    int size = 0;
    lockClients();
    size = (int) clients.size();
    unlockClients();
    return size;
}


size_t caThreadManager::GetRunningSize(void)
{
    HERE1();
    int size = 0;
    lockRunning();
    size = (int) running.size();
    unlockRunning();
    return size;
}


size_t caThreadManager::GetStoppedSize(void)
{
    HERE1();
    int size = 0;
    lockStopped();
    size = (int) stopped.size();
    unlockStopped();
    return size;
}


void caThreadManager::GetStatus(statusThreads &st)
{
    st.clients=GetClientsSize();
    st.running=GetRunningSize();
    st.stopped=GetStoppedSize();
    st.errors=errors;
}


void caThreadManager::StartClients(size_t max_run)
{
    HERE1();
    max_running=max_run;
    do
    {
        statusThreads st;
        GetStatus(st);
        auto i=st.running-st.stopped;
        auto end=st.clients-st.running;
        if(i<max_running && end>0)
        {
            Run(i);
        }
        else
        {
            break;
        }

    }
    while(1);
}


void  caThreadManager::lockRunning(void)
{
    auto res=-1;
    do
    {
        res=pthread_mutex_lock(&mMtxRun);
        if(res)
        {
            std::cerr<<"LOCK RUNNING ERROR"<<std::endl;
            break;
        }
    }
    while(res!=0);
}


void  caThreadManager::unlockRunning(void)
{
    auto res=-1;
    auto fail=0;
    do
    {
        res=pthread_mutex_unlock(&mMtxRun);
        if(res)
        {
            std::cerr<<"UNLOCK RUNNING ERROR"<<std::endl;
            fail++;
            if(fail>20)break;
            usleep(50000);
        }
    }
    while(res!=0);
}


void  caThreadManager::lockStopped(void)
{
    auto res=-1;
    auto fail=0;
    do
    {
        res=pthread_mutex_lock(&mMtxStop);
        if(res)
        {
            std::cerr<<"LOCK STOPPED ERROR"<<std::endl;
            fail++;
            if(fail>20)break;
            usleep(50000);
        }
    }
    while(res!=0);
}


void  caThreadManager::unlockStopped(void)
{
    auto res=-1;
    do
    {
        res=pthread_mutex_unlock(&mMtxStop);
        if(res)
        {
            std::cerr<<"UNLOCK STOPPED ERROR"<<std::endl;
            break;
        }
    }
    while(res!=0);
}


void  caThreadManager::lockClients(void)
{
    auto res=-1;
    auto fail=0;
    do
    {
        res=pthread_mutex_lock(&mMtxClients);
        if(res)
        {
            std::cerr<<"LOCK CLIENTS ERROR"<<std::endl;
            fail++;
            if(fail>20)break;
            usleep(50000);
        }
    }
    while(res!=0);
}


void  caThreadManager::unlockClients(void)
{
    auto res=-1;

    do
    {
        res=pthread_mutex_unlock(&mMtxClients);
        if(res)
        {
            std::cerr<<"UNLOCK CLIENTS ERROR"<<std::endl;
            break;
        }
    }
    while(res!=0);
}


int caThreadManager::ClientsTerminateSignal(void)
{
    int ret = pthread_cond_signal(&mCond);
    if (ret != 0)
    {
        std::cerr << "Cannot signalling condition" << std::endl;
    }
    return ret;
}


int caThreadManager::WaitTerminateClients(void)
{
    int ret = pthread_cond_wait(&mCond, &mMtxEnd);
    if (ret != 0)
    {
        std::cerr << "Cannot waiting condition" << std::endl;
    }
    return ret;
}

void caThreadManager::JoinAll()
{
    for (auto & th : stopped)
    {
        th->JoinThread();
    }
}

}

