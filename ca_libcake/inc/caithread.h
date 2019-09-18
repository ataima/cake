#ifndef THREAD_INTERFACE_FILE_HEADER
#define THREAD_INTERFACE_FILE_HEADER
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
namespace CA
{



typedef void * (*functor)(void *);
typedef void (*cleanctor)(size_t, int);


typedef enum tag_thread_status
{
    STOPPED,
    WAIT_SIGNAL,
    RUNNING,
    RESUME,
    TRY_EXIT,
    EXITED
} caThreadStatus;

typedef enum tag_thread_mode
{
    WAIT_ALWAYS,
    NO_WAIT,
    WAIT_ONLY_START,
    REQ_EXIT
} caThreadMode;

typedef enum tag_thread_schedule_mode
{
    ROUND_ROBIN,
    MORE_INCR,
    MODE_USER,
} caSchedulerPriorityMode;


#define MOREDEBUG 0

#if MOREDEBUG
#define HERE() std::cerr<<__func__<< "  : "<<__LINE__ <<std::endl;
#define HERE1() std::cerr<<mName<<" : "<<__func__<< "  : "<<__LINE__ << \
              "  status="<<this->mStatus<<"  mode="<<this->mMode<<"  index="<<(int)(unsigned long int)reqParam<<std::endl;
#else
#define HERE()
#define HERE1()
#endif
}

#endif /* THREAD_H */

