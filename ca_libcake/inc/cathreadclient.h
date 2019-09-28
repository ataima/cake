#ifndef CA_THREAD_CLIENT_H
#define CA_THREAD_CLIENT_H

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


#include <thread>
#include <mutex>
#include <condition_variable>

typedef void * (*functor)(void *);
typedef void (*cleanctor)(int, int);

typedef enum tag_thread_status
{
    STOPPED,
    WAIT_SIGNAL,
    RUNNING,
    RESUME,
    TRY_EXIT,
    EXITED
} caThreadStatus;


namespace CA
{

class caThreadClient
{
protected:
    caThreadStatus mStatus;
    std::thread *mThid;
    std::mutex mMtx;
    std::mutex mMtxSignal;
    std::condition_variable mCond;
    functor reqFunc;
    cleanctor cleanfunc;
    int mIndex;
    unsigned long int mTickCount;
    void *reqParam;
    char mName[32];


    bool CreateThread();
    void WaitForSignal();
    int ExecuteClient();
    void CondWait();
    void CondSignal();





public:
    explicit caThreadClient( int index = 0,cleanctor cc=nullptr);
    ~caThreadClient();
    bool InitThread(functor entry, void *param, const char *name);
    void SleepThread(unsigned int delay);
    void Resume();
    void ReqExit();
    void Reset();
    inline void finalize_cleanup(int result)
    {
        if (cleanfunc!=nullptr)
            cleanfunc(mIndex,result);
    }
    inline caThreadStatus getStatus()
    {
        return mStatus;
    }

    inline void setStatus(caThreadStatus m)
    {
        mStatus = m;
    }


    inline std::thread * getThreadId()
    {
        return mThid;
    }

    inline const char *getName()
    {
        return mName;
    }

    inline unsigned long int getTickCount()
    {
        return mTickCount;
    }

    inline size_t getIndex()
    {
        return mIndex;
    }

public:
    static void * entry_point(void *param);

};

}

#endif /* THREADCLIENT_H */

