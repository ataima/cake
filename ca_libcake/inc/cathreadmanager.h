#ifndef THREAD_MANAGER_FILE_HEADER
#define THREAD_MANAGER_FILE_HEADER


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


namespace CA
{


class caThreadManager;

typedef std::vector<caThreadClient *> thArray;
typedef int (*functor_nexttask)(caThreadManager *instance);

typedef struct tag_resutl_thread
{
    size_t index;
    int result;
} resultThread;

typedef struct tag_status_thread
{
    size_t clients;
    size_t running;
    size_t stopped;
    std::vector<resultThread> errors;
} statusThreads;

class caThreadManager
{
private:
    thArray clients;
    thArray running;
    thArray stopped;
    size_t max_running;
    std::vector<resultThread> errors;
    static pthread_mutex_t mMtxClients;
    static pthread_mutex_t mMtxRun;
    static pthread_mutex_t mMtxStop;
    static caThreadManager *instance;
private:
    bool Run(size_t index);
    size_t GetClientsSize(void);
    size_t GetRunningSize(void);
    size_t GetStoppedSize(void);
public:
    caThreadManager();
    ~caThreadManager();
    bool AddClient(functor func,void *param, size_t index, const char *name);

    void GetStatus(statusThreads &st);
    void StartClients(size_t max_run);
    void StopClients(void);
    bool Reset(void);

    inline bool haveErrors(void)
    {
        return !errors.empty();
    }

    inline static caThreadManager * getInstance(void)
    {
        return instance;
    }

    void lockRunning(void);
    void unlockRunning(void);
    void lockStopped(void);
    void unlockStopped(void);
    void lockClients(void);
    void unlockClients(void);

    void finalize(size_t index,int result);
public:
    static void finalize_client(size_t index,int result);
};


}

#endif

