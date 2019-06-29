
#include "caminiXml.h"
#include "calogiface.h"
#include <iostream>
#include "caargv.h"


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
IOptionArgvManager *IOptionArgvManager::instance=nullptr;


argvManager::argvManager(size_t reqOptionNum)
{


    if(instance!=nullptr)
    {
        std::stringstream ss;
        ss<<"Error : duplicate instance of argvManager ";
        throw std::runtime_error(ss.str());
    }
    instance=this;
    optionsDir.insert(optionsDir.begin(),reqOptionNum,nullptr);

}


argvManager::~argvManager()
{
    for( std::pair<const std::string ,CA::IOptionArgv *> & it: options)
    {
        delete it.second;
    }
    delete instance;
    instance=nullptr;
}




void argvManager::Parse(const char *argv[], size_t size)
{
    size_t index = 1;
    if(index==size)
    {
        throw std::runtime_error("missing xml input file..");
    }
    while (index < size)
    {
        if (IOptionArgv::isOption(argv[index]))
        {
            getOption(argv[index]).parse(argv, size, index);
        }
        else
        {
            args.push_back(argv[index]);
            index++;
        }
    }
    prepareInput();
}

void argvManager::addOption(IOptionArgv *reqOpt)
{
    const std::string &name=reqOpt->getName();
    if(!name.empty())
    {
        options[name]=reqOpt;
        size_t offset=reqOpt->getOffset();
        if(offset<optionsDir.size())
        {
            optionsDir.at(offset)=reqOpt;
        }
        else
        {
            std::stringstream ss;
            ss<<" the requested option "<<reqOpt->getName() <<" cannot place at  offset"<<offset<<" because the totak number of options declare is "<<optionsDir.size();
            throw std::runtime_error(ss.str().c_str());
        }
    }
    else
    {
        throw std::runtime_error("Invalid option name!");
    }
}

IOptionArgv & argvManager::getOption(const std::string & opt)
{

    auto it = options.find(opt);
    if (it != options.end())
    {
        return  *it->second;
    }
    std::stringstream ss;
    ss<<"Unknow option parameter '"<< opt<<"'";
    throw std::runtime_error(ss.str());
}

IOptionArgv & argvManager::getOption(size_t offset)
{
    if(offset<optionsDir.size())
    {
        return *optionsDir.at(offset);
    }
    else
    {
        std::stringstream ss;
        ss<<"Try to access to outbound on array options";
        throw std::runtime_error(ss.str().c_str());
    }
}

bool argvManager::saveAsXml(const _cbt * filename)
{
    auto res = false;
    miniXmlNode root("qxmlc", "");
    IXmlNode *argv = root.add("argv", "");
    if (argv != nullptr)
    {
        for ( auto it : options )
        {
            argv->add(it.first,it.second->getStringValue());
        }
    }
    std::string allargs;
    for ( const std::string & it : args)
    {
        allargs+=(" ");
        allargs+=it;
    }
    root.add("args", allargs);
    root.save(filename);
    return res;
}





void  argvManager::prepareInput()
{
    char curdir[1024]= {0};
    getcwd(curdir, sizeof(curdir));
    if(!args.empty())
        argvManager::replaceRelative(args,curdir);
    else
    {
        args.push_back(curdir);
    }
}


void   argvManager::replaceRelative(stringList & ls,const char *abspath)
{
    if( abspath!=nullptr)
    {
        for (auto it : ls)
        {
            if(it==".")it=abspath;
            else if(it=="..")
            {
                const char* parent=dirname((char *)abspath);
                if(parent[0]=='.')
                {
                    it=abspath;
                }
                else
                {
                    it=parent;
                }
            }
            else if(it.at(0)=='.' && it.at(1)=='.' && it.at(2)=='/')
            {
                std::string replace=dirname((char *)abspath);
                if(replace[0]=='.')
                {
                    replace=abspath;
                }
                replace+=&((it)[2]);
                it=replace;
            }
            else if(it.at(0)=='.' && it.at(1)=='/')
            {
                std::string replace=abspath;
                replace+=&((it)[1]);
                it=replace;
            }
        }
    }
}

}