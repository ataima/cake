
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
#include <sys/stat.h>

namespace CA
{


bool caUtils::checkDirExistOrCreate(std::string & dir)
{
    auto res=caUtils::checkDirExist(dir);
    if(!res)
    {
        res=(mkdir(dir.c_str(), 0777)==0);
    }
    return res;
}


bool caUtils::checkDirExist(std::string & dir)
{
    auto res=false;
    struct stat sb= {0};
    if(!dir.empty())
    {
        if (stat(dir.c_str(), &sb) == 0 )
        {
            res=S_ISDIR(sb.st_mode);
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
    struct stat sb= {0};
    if(!file.empty())
    {
        if (stat(file.c_str(), &sb) == 0 )
        {
            return S_ISREG(sb.st_mode);
        }
    }
    return false;
}

/**
 * compare two file :
 * if file 1 is older than file2 return true : ex source.cpp older source.o
 * @param file1 name
 * @param file2 name
 * @return bool
 */
bool caUtils::compareChangeDate(std::string & root, std::string & child)
{
    auto res=false;
    struct stat root_stat= {0};
    struct stat child_stat= {0};
    if(!root.empty())
    {
        if (stat(root.c_str(), &root_stat) == 0 )
        {
            if(!S_ISREG(root_stat.st_mode))
                return res;
        }
    }
    if(!child.empty())
    {
        if (stat(child.c_str(), &child_stat) == 0 )
        {
            if(!S_ISREG(child_stat.st_mode))
                return res;
        }
    }
    if (root_stat.st_mtim.tv_sec == child_stat.st_mtim.tv_sec)
        res= (root_stat.st_mtim.tv_nsec < child_stat.st_mtim.tv_nsec);
    else
        res= (root_stat.st_mtim.tv_sec < child_stat.st_mtim.tv_sec);
    return res;
}


}