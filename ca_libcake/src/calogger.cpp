#include "calogger.h"
/**************************************************************
Copyright(c) 2015 Angelo Coppi

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
#include <ctime>
#include <thread>
#include <chrono>
#include <iomanip>
#include <stdarg.h>
#include <iostream>

namespace CA
{

#if _LOGGER_

unsigned short currentLogLevel=7; // print all

static const char *msginfo[]=
{
    "EMERG","ALERT","CRIT","ERR","WARNING","NOTICE","INFO","DEBUG","HUH!",
    "HUH!","HUH!","HUH!","HUH!"
};



ILogger * ILogger::instance = nullptr;



Logger::Logger() :
    notify(false),
    done(false),
    th(nullptr),
    current_printer(nullptr)
{
    if (instance == nullptr)
        instance = this;
    t_start = std::chrono::steady_clock::now();
    currentLogLevel=7;
}

Logger::~Logger()
{
    if (th != nullptr)
    {
        done = true;
        cond_var.notify_one();
        if (th->joinable())
            th->join();
        delete th;
        th = nullptr;
    }
    delete current_printer;
    current_printer = nullptr;
    while (!io.empty())
    {
        delete io.front();
        io.pop();
    }

    instance = nullptr;
    currentLogLevel=0;
}

void Logger::log(int level,const char *fmt, ... )
{
    char dest[0x3fff];
    va_list argptr;
    //producer...
    auto param= new ILogParam;
    param->time = std::chrono::steady_clock::now();
    if (!done)
    {
        if (!th)
        {
            if (current_printer != nullptr)
            {
                //only first time
                th = new std::thread(Logger::entry, this);
            }
        }
        std::unique_lock<std::mutex> lock(mtx);
        va_start(argptr, fmt);
        vsnprintf(dest,sizeof(dest), fmt, argptr);
        va_end(argptr);
        param->level=level;
        param->msg=dest;
        io.push(param);
        notify = true;
        cond_var.notify_one();
    }
}


void Logger::print(ILogParam *p)
{
    if (current_printer )
    {
        if (p)
        {
            std::string msg;
            std::stringstream ts;
            ts << "%s[" <<std::setw(12)<< (p->time - t_start).count() << " %sns%s ]%s "<<msginfo[p->level]<<" > %s"<<p->msg<<"%s%s";
            t_start = p->time;
            msg = ts.str();
            current_printer->out(p->level,msg);
            msg.clear();
        }
    }
}

ILogParam * Logger::remove()
{
    ILogParam *param = nullptr;
    std::unique_lock<std::mutex> lock(mtx);
    if (!notify)
    {
        //cond_var.wait_for(lock, std::chrono::milliseconds(100));
        cond_var.wait(lock);
    }
    if (!io.empty())
    {
        param = io.front();
        io.pop();
    }
    notify = !io.empty();
    return param;
}


void Logger::enqueue()
{

    while(!done)
    {
        ILogParam *param = remove();
        if(param)
        {
            print(param);
            delete param;
        }
    }
    if (done)
    {
        std::unique_lock<std::mutex> lock(mtx);
        while (!io.empty())
        {
            delete io.front();
            io.pop();
        }
        cond_var.notify_one();
    }
}

void Logger::entry(ILogger *current)
{
    if (current)
    {
        auto log = dynamic_cast<Logger*>(current);
        if(log)
            log->enqueue();
    }
}



void Logger::reset()
{
    std::unique_lock<std::mutex> lock(mtx);
    done = true;
    cond_var.notify_one();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    cond_var.wait(lock);
    if (th != nullptr)
    {
        th->join();
        delete th;
        th = nullptr;
    }
    if (current_printer != nullptr)
    {
        delete current_printer;
        current_printer = nullptr;
    }
}






void DefaultPrinter::out( int level, std::string & msg)
{

    const char * colors[]=
    {
        RED,RED,RED,
        RED,BLUE_LIGHT,CYAN,WHITE,GRAY_DARK,nullptr
    };
    if(level<0)level=0;
    if(level>LOG_DEBUG)level=LOG_DEBUG+1;
    fprintf(stderr ,msg.c_str(),GREEN_LIGHT,YELLOW,GREEN_LIGHT,WHITE,colors[level],REPLACE,"\n");
}


}

#endif
