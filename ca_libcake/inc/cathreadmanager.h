#ifndef CA_THREAD_MANAGER_H
#define CA_THREAD_MANAGER_H

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

#include <vector>
#include <cathreadclient.h>


namespace CA
{

class caThreadManager;




typedef std::vector<caThreadClient *> thArray;


typedef struct tag_status_thread
{
    size_t clients;
    size_t running;
    size_t stopped;
    int errors;
} statusThreads;

class caThreadManager
{
private:
    thArray clients;
    std::vector<int> running;
    std::vector<int> stopped;
    int max_running;
    int errors;
    std::mutex mMtxRun;
    std::mutex mMtxStop;
    std::mutex mMtxEnd;
    std::mutex mMtxGo;
    std::condition_variable mCondEnd;
    static caThreadManager *instance;
private:
    bool Run(int index);
    void pushRunning(int index);
    void pushStopped(int index);
    int  GetRunningSize();
    int  GetStoppedSize();
    void ClientsTerminateSignal();
    void finalize(int index,int result);
public:
    caThreadManager();
    ~caThreadManager();
    bool AddClient(functor func,void *param, int index, const char *name);
    void GetStatus(statusThreads &st);
    void StartClients(int max_run);
    void Reset();
    void WaitTerminateClients();
    inline bool haveErrors()
    {
        return (errors!=0);
    }

    inline static caThreadManager * getInstance()
    {
        return instance;
    }


public:
    static void finalize_client(int index,int result);
};

}

#endif /* THREANMANAGER_H */

