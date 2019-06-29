#include <stdio.h>
#include <string>
#include <unistd.h>
#include <sys/stat.h>
#include <chrono>
#include <ctime>
#include "calogiface.h"
#include "caminiXml.h"
#include "camain.h"




#define WHITE "\e[1;37m"
#define RED_LIGHT "\e[1;31m"
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

int main ( int argc, const char * argv[])
{

    bool result=false;
    std::chrono::steady_clock::time_point t_start = std::chrono::steady_clock::now();
    CA::mainAppExecutor executor;

    try
    {
        result = executor.init(argv,argc);
        if(result)
            executor.execute();
    }
    catch(std::runtime_error &e)
    {
        LogError("Cannot continue for exception : %s",e.what());
    }
    catch (...)
    {
        LogError("Unknow exception ...");
    }

    std::chrono::steady_clock::time_point t_stop= std::chrono::steady_clock::now();
    LogInfo("Total time : \e[1;31m %ld \e[1;36m ns \e[1;37m, bye....",
            (t_stop - t_start).count());
    sleep(1);
    exit (result);
}
