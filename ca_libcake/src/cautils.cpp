
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



#include "cautils.h"
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <cstring>

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
bool caUtils::compareFileChangeDate(std::string & root, std::string & child)
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

/**
 * compare a  file  with dir :
 * if file 1 is older than dir return true : ex source.cpp older source.o
 * @param file1 name
 * @param dir name
 * @return bool
 */
bool caUtils::compareDirChangeDate(std::string & root, std::string & path)
{
    auto res=false;
    struct stat root_stat= {0};
    struct stat path_stat= {0};
    if(!root.empty())
    {
        if (stat(root.c_str(), &root_stat) == 0 )
        {
            if(!S_ISREG(root_stat.st_mode))
                return res;
        }
    }
    if(!path.empty())
    {
        if (stat(path.c_str(), &path_stat) == 0 )
        {
            if(!S_ISDIR(path_stat.st_mode))
                return res;
        }
    }
    if (root_stat.st_mtim.tv_sec == path_stat.st_mtim.tv_sec)
        res= (root_stat.st_mtim.tv_nsec < path_stat.st_mtim.tv_nsec);
    else
        res= (root_stat.st_mtim.tv_sec < path_stat.st_mtim.tv_sec);
    return res;
}


bool caUtils::removeDir(std::string & path)
{
    size_t path_len;
    char *full_path;
    DIR *dir;
    struct stat stat_path, stat_entry;
    struct dirent *entry;
    stat(path.c_str(), &stat_path);

    if(S_ISREG(stat_path.st_mode))
    {
        unlink(path.c_str());
        return true;
    }
    // if path does not exists
    if (S_ISDIR(stat_path.st_mode) == 0)
    {
        return true;
    }
    else
    {

        // if not possible to read the directory for this user
        if ((dir = opendir(path.c_str())) == NULL)
        {
            return false;
        }


        // iteration through entries in the directory
        while ((entry = readdir(dir)) != NULL)
        {

            // skip entries "." and ".."
            if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
                continue;

            // determinate a full path of an entry
            std::string full_path=path;
            std::string relpath=entry->d_name;
            caUtils::appendPath(full_path,relpath);
            stat(full_path.c_str(), &stat_entry);
            // recursively remove a nested directory
            if (S_ISDIR(stat_entry.st_mode) != 0)
            {
                caUtils::removeDir(full_path);
            }
            else
            {
                // remove a file object
                if (unlink(full_path.c_str()) != 0)
                    return false;
            }
        }
        // remove the devastated directory and close the object of it
        if (rmdir(path.c_str()) != 0)
            return false;
        closedir(dir);
        return true;
    }
    return false;
}


bool caUtils::baseName(std::string & path, std::string & filename)
{
    filename.clear();
    if(!path.empty())
    {
        std::string::size_type s=path.rfind('/');
        if(s!=std::string::npos)
        {
            s++;
            while(s<path.size())
            {
                filename+=path[s++];
            }
        }
        else
        {
            filename=path;
        }
    }
    return (!filename.empty());
}

bool caUtils::baseNameNoExt(std::string & path, std::string & filename)
{
    filename.clear();
    caUtils::baseName(path,filename);
    if(!filename.empty())
    {
        std::string::size_type s=filename.rfind('.');
        if(s!=std::string::npos)
        {
            filename.erase(s,filename.size());
        }
    }
    return (!filename.empty());
}

bool caUtils::dirName(std::string & path, std::string & dirname)
{
    dirname.clear();
    if(!path.empty())
    {
        std::string::size_type s=path.rfind('/');
        if(s!=std::string::npos)
        {
            std::string::size_type p=0;
            while(p<s)
            {
                dirname+=path[p++];
            }
        }
        else
        {
            dirname="/";
        }
    }
    return (!dirname.empty());
}

bool caUtils::baseExt(std::string & file, std::string & ext)
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

bool caUtils::toUpperAlpha(std::string & src, std::string & dst)
{
    dst.clear();
    for( auto c : src)
    {
        if(::isalpha(c))
            dst.push_back(std::toupper(c));
    }
    return !dst.empty();
}

bool caUtils::toUpperAscii(std::string & src, std::string & dst)
{
    dst.clear();
    for( auto c : src)
    {
        if(::isascii(c))
            dst.push_back(std::toupper(c));
    }
    return !dst.empty();
}

bool caUtils::changeExt(std::string & name, const char *ext)
{
    auto res = false;
    if(!name.empty())
    {
        std::string::size_type  s=name.find('.');
        if(s!=std::string::npos)
        {
            s++;
            name.erase(s,name.size()-s);
            name+=ext;
            res=true;
        }
    }
    return res;
}


}