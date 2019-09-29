
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
#include <errno.h>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <set>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cathreadclient.h>
#include <cathreadmanager.h>
#include <calogiface.h>


namespace CA
{


caThreadManager *caThreadManager::instance = nullptr;

caThreadManager::caThreadManager()
{
    max_running=1;
    clients.clear();
    running.clear();
    stopped.clear();
    if (instance != nullptr)
    {
        std::cerr << "caThreadManager::instance already set !!" << std::endl;
    }
    instance = this;
    errors=0;
}

caThreadManager::~caThreadManager()
{
    for(auto th: clients)
    {
        th->ReqExit();
        delete th;
    }
    mMtxRun.lock();
    running.clear();
    mMtxRun.unlock();
    mMtxStop.lock();
    stopped.clear();
    mMtxStop.unlock();
    instance=nullptr;
}



bool caThreadManager::AddClient(functor func, void *param,  int index, const char *name)
{
    auto client = new caThreadClient(index,caThreadManager::finalize_client);
    client->InitThread(func, param, name);
    clients.push_back(client);
    return true;
}


void caThreadManager::pushRunning(int index)
{
    std::unique_lock<std::mutex> lck(mMtxRun);
    running.push_back(index);
}


void caThreadManager::pushStopped(int index)
{

    std::unique_lock<std::mutex> lck(mMtxStop);
    stopped.push_back(index);
}


int caThreadManager::GetRunningSize()
{
    auto size = 0;
    std::unique_lock<std::mutex> lck(mMtxRun);
    size = (int) running.size();
    return size;
}


int caThreadManager::GetStoppedSize()
{
    int size = 0;
    std::unique_lock<std::mutex> lck(mMtxStop);
    size = (int) stopped.size();
    return size;
}


void caThreadManager::GetStatus(statusThreads &st)
{
    st.clients=clients.size();
    st.running=GetRunningSize();
    st.stopped=GetStoppedSize();
    st.errors=errors;
}


bool caThreadManager::Run(int index)
{
    auto result = false;
    if(index<clients.size())
    {
        auto clientThread =clients.at(index);;
        if(clientThread!=nullptr &&  clientThread->getStatus() == caThreadStatus::WAIT_SIGNAL )
        {
            clientThread->ToRun();
            pushRunning(index);
            result=true;
        }
    }
    return result;
}

void  caThreadManager::finalize_client(int index,int error)
{
    caThreadManager *manager=caThreadManager::getInstance();
    if(manager!=nullptr)
    {
        manager->finalize(index,error);
    }
}

void  caThreadManager::finalize( int index, int result)
{
    pushStopped(index);
    if(result!=0)errors++;
    auto crun=GetRunningSize();
    auto cclient=clients.size();
    auto cstop=GetStoppedSize();
    {
        std::unique_lock<std::mutex> lck(mMtxGo);
        if(crun<cclient)
            Run(crun);
    }
    if(cstop==cclient)
    {
        ClientsTerminateSignal();
    }
}




void  caThreadManager::Reset()
{
    for(auto th: clients)
    {
        th->Reset();
    }
    mMtxRun.lock();
    running.clear();
    mMtxRun.unlock();
    mMtxStop.lock();
    stopped.clear();
    mMtxStop.unlock();
}







void caThreadManager::StartClients(int max_run)
{
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
    while(true);
}





void caThreadManager::ClientsTerminateSignal()
{
    std::unique_lock<std::mutex> lck(mMtxEnd);
    mCondEnd.notify_one();
    //LogCritical("SCHEDULER : TERMINATE ALL JOBS SIGNAL")
}


void caThreadManager::WaitTerminateClients()
{
    std::unique_lock<std::mutex> lck(mMtxEnd);
    mCondEnd.wait(lck);
    LogCritical("SCHEDULER : TERMINATE ALL JOBS")
}

}