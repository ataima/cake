#ifndef CA_LOG_INTERFACES
#define CA_LOG_INTERFACES




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

#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <chrono>
#include <syslog.h>


#define _LOGGER_ 1






namespace CA
{


#define WHITE "\e[1;37m"
#define GRAY_LIGHT "\e[0;37m"
#define GRAY_DARK "\e[1;30m"
#define BLUE "\e[0;34m"
#define BLUE_LIGHT "\e[1;34m"
#define GREEN "\e[0;32m"
#define GREEN_LIGHT "\e[1;32m"
#define CYAN "\e[0;36m"
#define CYAN_LIGHT "\e[1;36m"
#define RED "\e[0;31m"
#define RED_LIGHT "\e[1;31m"
#define PURPLE "\e[0;35m"
#define PURPLE_LIGHT "\e[1;35m"
#define BROWN "\e[0;33m"
#define YELLOW "\e[1;33m"
#define BLACK "\e[0;30m"
#define REPLACE "\e[0m"

#if _LOGGER_



class IPrinter
{
public :
    virtual void out( int level, std::string & msg) = 0;
    virtual ~IPrinter() {}
};


extern unsigned short currentLogLevel;

class ILogger
{
protected:
    static ILogger *instance;
public:
    virtual void log(int level,const char *__fmt, ... ) = 0;
    static  ILogger * getInstance()
    {
        return instance;
    }
    virtual void setOutput(IPrinter *printer) = 0;
    virtual IPrinter *output() = 0;
    virtual void reset()=0;
    virtual void setLogLevel(int level)
    {
        CA::currentLogLevel=level;
    }
    virtual int getLogLevel()
    {
        return (int)(CA::currentLogLevel);
    }
    virtual ~ILogger()
    {
        instance=nullptr;
    }
};

}


#define LogEmergency(...) if(CA::currentLogLevel>=0)CA::ILogger::getInstance()->log(0,__VA_ARGS__)
#define LogAlert(...)   if(CA::currentLogLevel>1)CA::ILogger::getInstance()->log(1,__VA_ARGS__)
#define LogCritical(...)   if(CA::currentLogLevel>2)CA::ILogger::getInstance()->log(2,__VA_ARGS__)
#define LogError(...)   if(CA::currentLogLevel>3)CA::ILogger::getInstance()->log(3,__VA_ARGS__)
#define LogWarning(...)   if(CA::currentLogLevel>4)CA::ILogger::getInstance()->log(4,__VA_ARGS__)
#define LogNotice(...)   if(CA::currentLogLevel>5)CA::ILogger::getInstance()->log(5,__VA_ARGS__)
#define LogInfo(...)   if(CA::currentLogLevel>6)CA::ILogger::getInstance()->log(6,__VA_ARGS__)
#define LogDebug(...)   if(CA::currentLogLevel>7)CA::ILogger::getInstance()->log(7,__VA_ARGS__)


#else

#define LogEmergency(...)
#define LogAlert(...)
#define LogCritical(...)
#define LogError(...)
#define LogWarning(...)
#define LogNotice(...)
#define LogInfo(...)
#define LogDebug(...)
#endif


#endif // CA_LOG_INTERFACES

