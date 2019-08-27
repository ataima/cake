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

#include <caconfenv.h>
#include <calogger.h>


namespace CA
{

caGetConfEnv::caGetConfEnv(const char *home,const char *pwd,const char *user)
{
    add("USER",user);
    add("HOME",home);
    add("PWD",pwd);
}

caGetConfEnv::caGetConfEnv( IGetConfEnv * _env)
{
    if(_env!=nullptr)
        append(_env);
}


caGetConfEnv::~caGetConfEnv()
{
    keyVal.clear();
}

bool caGetConfEnv::add(const char *key,std::string value)
{
    bool res=false;
    auto it=keyVal.find(key);
    if(it==keyVal.end())
    {
        std::string replaced;
        replaceValue(value,replaced);
        std::pair<const char *,std::string> p(key,replaced);
        keyVal.insert(p);
        res=true;
    }
    else
    {
        LogInfo("Warning env %s already defined with value %s",
                it->first.c_str(),it->second.c_str());
    }
    return res;
}

bool caGetConfEnv::add(envMap & tmap)
{
    bool res=false;
    for(auto n: tmap)
    {
        res=add(n.first.c_str(),n.second);
    }
    return res;
}

std::string * caGetConfEnv::getValue(const char * key)
{
    std::string *res= nullptr;
    auto it=keyVal.find(key);
    if(it!=keyVal.end())
    {
        res=&it->second;
    }
    else
    {
        std::string system_env=std::getenv(key);
        if(system_env.empty())
            LogInfo("Warning undefined env %s ",key);
        else
            LogInfo("Warning load system env : %s",key);
    }
    return res;
}


// data una string rimpiazza tutte le pseudo variabili bash ($XXXXX)
// con il valore della mappa . USER HOME e PWD predefinite
// ROOT mainstream
void caGetConfEnv::replaceValue(std::string & in, std::string & out)
{
    auto  pos=0;
    auto  maxL=in.size();
    while(pos<maxL)
    {
        if(in[pos]=='$')
        {
            pos++;
            std::string key;
            while(pos<maxL)
            {
                char t=in[pos];
                if((t>='A' && t<='Z') || t=='_' )
                {
                    key+=t;
                    pos++;
                }
                else
                    break;
            }
            if(!key.empty())
            {
                std::string *res=getValue(key.c_str());
                if(res== nullptr)
                {
                    throw std::runtime_error("Unknow env : " + key);
                }
                else
                {
                    out+=*res;
                }
            }
        }
        else
        {
            out+=in[pos];
            pos++;
        }
    }
}

void caGetConfEnv::dump(const char *envname)
{
    for (auto const it : keyVal)
    {
        LogInfo("%s : env %s=%s",envname,it.first.c_str(),it.second.c_str());
    }
}


void caGetConfEnv::append( IGetConfEnv * root )
{
    if(root!=nullptr)
    {
        keyVal.insert(root->getMap().begin(),root->getMap().end());
    }
}


}