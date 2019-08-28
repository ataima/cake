
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
#include <string>
#include "cautils.h"
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

namespace CA
{
bool caUtils::checkDirExistOrCreate(std::string & dir)
{
    auto res=false;
    struct stat sb;
    if(!dir.empty())
    {
        if (!((stat(dir.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))))
        {
            if( mkdir(dir.c_str(), 0777)==0)
                res=true;
        }
    }
    return res;
}

bool caUtils::getFileName(std::string & file, std::string & name)
{
    name.clear();
    if(!file.empty())
    {
        std::string::size_type  s=file.find('.');
        if(s!=std::string::npos)
        {
            std::string::size_type p=0;
            while(p<s)
            {
                name+=file[p++];
            }
        }
    }
    return !name.empty();
}

bool caUtils::getFileExt(std::string & file, std::string & ext)
{
    ext.clear();
    if(!file.empty())
    {
        std::string::size_type  s=file.find('.');
        if(s!=std::string::npos)
        {
            s++;
            while(s<file.size())
            {
                ext+=file[s++];
            }
        }
    }
    return !ext.empty();
}

void caUtils::appendPath(std::string & root,std::string & path)
{
#ifdef  __linux__
    root+="/";
    root+=path;
#else
    root+="\\"
          root+=path;
#endif
}

bool caUtils::checkFileExist(std::string & file)
{
    struct stat sb;
    if(!file.empty())
    {
        if (stat(file.c_str(), &sb) == 0 )
        {
            return S_ISREG(sb.st_mode);
        }
    }
    return false;
}



}