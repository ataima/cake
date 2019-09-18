#ifndef THREAD_CLIENT_FILE_HEADER
#define THREAD_CLIENT_FILE_HEADER

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

#include <caithread.h>


namespace CA
{




class caThreadClient
{
    caThreadStatus mStatus;
    caThreadMode mMode;
    pthread_t *mThid;
    static pthread_mutex_t mMtx;
    pthread_cond_t mCond;
    functor reqFunc;
    cleanctor cleanfunc;
    size_t mIndex;
    unsigned long int mTickCount;
    void *reqParam;
    char mName[32];


    bool CreateThread();
    int WaitForSignal(void);
    int ExecuteClient(void);
    int Lock(void);
    int Unlock(void);
    int CondWait(void);
    int CondSignal(void);
    void DestroyThread(void);
    void JoinThread(void);
    inline void finalize_cleanup(int result)
    {
        if (cleanfunc!=nullptr)
            cleanfunc(mIndex,result);
    }


public:
    caThreadClient( size_t index = 0,cleanctor cc=nullptr);
    ~caThreadClient();
    bool InitThread(functor entry, void *param, const char *name);
    void SleepThread(unsigned int delay);
    void Resume(void);
    void ReqExit(void);
    void Reset(void);

    inline caThreadStatus getStatus(void)
    {
        return mStatus;
    }

    inline void setStatus(caThreadStatus m)
    {
        mStatus = m;
    }

    inline caThreadMode getMode(void)
    {
        return mMode;
    }

    inline pthread_t * getThreadId(void)
    {
        return mThid;
    }

    inline const char *getName(void)
    {
        return mName;
    }

    inline int getTickCount(void)
    {
        return mTickCount;
    }

    inline size_t getIndex(void)
    {
        return mIndex;
    }

public:
    static void * entry_point(void *param);
    static void cleanup_point(void *param);

};



}


#endif /* THREADCLIENT_H */

