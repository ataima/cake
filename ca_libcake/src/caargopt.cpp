
#include "calogiface.h"
#include "caminiXml.h"
#include "calogiface.h"
#include <iostream>
#include "caargopt.h"
#include "caargv.h"
#include "calogiface.h"
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <libgen.h>
#include <numeric>


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


bool IOptionArgv::isOption(const _cbt *opt)
{
    auto res = false;
    if (opt[0] == '-' && opt[1] == '-')
    {
        res = true;
    }
    return res;
}


bool optionArgvBoolParser::parse(const char * /* argv */ [],
                                 size_t  /* size */,
                                 size_t &index)
{
    status = true;
    index++;
    return true;
}


const _cbt * optionArgvBoolParser::getStringValue()
{
    if (status)
        return "1";
    return "0";
}


bool optionArgvStringParser::parse(const char *argv[], size_t size,
                                   size_t &index)
{
    status=true;
    index++;
    if (index < (size - 1))
    {
        inputS = argv[index];
        index++;
        return true;
    }
    else
    {
        std::stringstream ss;
        ss << "Error : option '" << this->optionName << "' missing string input value";
        throw std::runtime_error(ss.str());
    }
}


const _cbt * optionArgvStringParser::getStringValue()
{
    if(inputS.empty())
    {
        std::stringstream ss;
        ss << "Error : option '" << this->optionName << "' empty value ";
        throw std::runtime_error(ss.str());
    }
    return inputS.c_str();
}


bool optionArgvIntParser::parse(const char *argv[], size_t size,
                                size_t &index)
{
    status = true;
    index++;
    if (index < (size - 1))
    {
        inputI= ::strtol(argv[index], nullptr, 10);
        if (inputI < min_value)
        {
            std::stringstream ss;
            ss << "Error : " << optionName << " min value = " << min_value << " input : " << inputI;
            throw std::runtime_error(ss.str());
        }
        if (inputI > max_value)
        {
            std::stringstream ss;
            ss << "Error : " << optionName << " max value = " << max_value << " input : " << inputI;
            throw std::runtime_error(ss.str());
        }
        index++;
    }
    else
    {
        std::stringstream ss;
        ss << "Error : option '" << this->optionName << "' missing number input value";
        throw std::runtime_error(ss.str());
    }
    return true;
}

const _cbt * optionArgvIntParser::getStringValue()
{
    std::stringstream ss;
    ss << inputI << " [ "<<min_value<<" - "<<max_value<<" ] ";
    return ss.str().c_str();
}

}