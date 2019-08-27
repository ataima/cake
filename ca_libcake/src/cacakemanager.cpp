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

#include "calogiface.h"
#include "calogger.h"
#include "cacakemanager.h"
#include "calayerconf.h"
#include <caconfenv.h>
#include <cstdlib>
#include <sys/stat.h>


namespace CA
{

cakeManager::cakeManager()
{
    env= new caGetConfEnv(std::getenv("HOME"),std::getenv("PWD"),std::getenv("USER"));
}

cakeManager::~cakeManager()
{
    reset();
}


bool cakeManager::run(const std::string &conf_file)
{
    auto res=false;
    if(!conf_file.empty())
    {
        if(conf.loadFromXml(conf_file))
        {
            if(conf.defaults.step.empty())
            {
                LogError("No builds step available, please set cake.conf.default.step");
                exit(1);
            }
            else
            {
                prepareDefaultEnv();
                prepareWorkDirs();
                logMainEnv("main_env_setup.log");
                LogInfo("%d build steps",conf.defaults.step.size());
                for (auto &it : conf.defaults.step)
                {
                    CAXml_Main_Defaults_Step *step=dynamic_cast<CAXml_Main_Defaults_Step *>(it);
                    LogInfo("Step %s : %s",step->name.c_str(),step->info.c_str() );
                    if(step->layer.empty())
                    {
                        std::string msg("error : no project included!");
                        sys_throw(msg);
                    }
                    else
                    {
                        // crea associazione tra step e progetto dichiarato
                        CAXml_Layer *slayer=new CAXml_Layer();
                        if(slayer)
                        {
                            std::string layers;
                            env->getValue("LAYERS",layers);
                            if(layers.empty())
                            {
                                std::stringstream ss;
                                ss<<"error undefined layers in configuration xml file : ";
                                std::string msg=ss.str();
                                sys_throw(msg);
                            }
                            std::string layer_name=layers+"/"+step->layer;
                            if(slayer->loadFromXml(layer_name))
                            {
                                LogInfo ("Step %s : create environment variables",step->name.c_str());
                                LogInfo ("Step %s : create jobs by layer :%s",step->name.c_str(),layer_name.c_str() );
                                jobs.push_back(new caJobStep(step,slayer));
                            }
                            else
                            {
                                std::stringstream ss;
                                ss<<"error cannot load layer xml file : "<<layer_name;
                                std::string msg=ss.str();
                                sys_throw(msg);
                            }
                        }
                    }
                }
                jobs.prepareStep(env);
            }
        }
        else
        {
            std::string msg;
            msg="Cannot load xml file : %s"+conf_file;
            sys_throw(msg);
        }
    }
    return res;
}

void cakeManager::reset ()
{
    delete env;
    jobs.reset();
}


void cakeManager::prepareDefaultEnv(void)
{
    if(!conf.conf.root.empty())
    {
        envMap tmp;
        conf.conf.toMap(tmp,true);
        env->add("ROOT",conf.conf.root); // must be the root of all env var
        if(!tmp.empty())
        {
            auto it_repo=tmp.find("ROOT");
            tmp.erase(it_repo);
            env->add(tmp);
        }
    }
    else
    {
        std::string msg("Invalid conf file: ROOT env must be set!");
        sys_throw(msg);
    }
}

inline static int check_dir_exist_or_create(const char *dir)
{
    struct stat sb;


    if(! ((stat(dir, &sb) == 0 && S_ISDIR(sb.st_mode))))
    {
        LogInfo("Not exist , create working directory : %s",dir);
        return mkdir(dir,0777);
    }
    else
    {
        LogInfo("Working directory : %s exist",dir);
    }
    return 0;
}


void cakeManager::prepareWorkDirs(void)
{
    const char * workdirs[]= {"BUILD","IMAGES","LAYERS","REPO","STATUS","LOGS","SOURCES","STORE",nullptr};
    const char * tmpdir=nullptr;
    auto i=0;
    while(1)
    {
        std::string * replaced;
        tmpdir=workdirs[i];
        if(tmpdir!= nullptr)
        {
            std::string replaced;
            env->getValue(workdirs[i],replaced);
            if(!replaced.empty())
                check_dir_exist_or_create(replaced.c_str());
        }
        else break;
        i++;
    }
}


void  cakeManager::logMainEnv(const char *logname)
{
    std::string logdir;
    env->getValue("LOGS",logdir);
    std::string logfile=logdir+"/"+logname;
    FilePrinter printer (logfile.c_str());
    CA::ILogger::getInstance()->addOutput(&printer);
    env->dump("Main configuration");
    CA::ILogger::getInstance()->sync();
    CA::ILogger::getInstance()->removeOutput(&printer);
}

}