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
#include "cacakemanager.h"
#include "calayerconf.h"
#include <caconfenv.h>
#include <cstdlib>


namespace CA
{

cakeManager::cakeManager()
{
    env= new caGetConfEnv(std::getenv("HOME"),std::getenv("PWD"),std::getenv("USER"));
}

cakeManager::~cakeManager()
{
    delete env;
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
                LogInfo("%d build steps",conf.defaults.step.size());
                for (auto &it : conf.defaults.step)
                {
                    CAXml_Main_Defaults_Step *step=dynamic_cast<CAXml_Main_Defaults_Step *>(it);
                    LogInfo("Step %s : %s",step->name.c_str(),step->info.c_str() );
                    if(step->projects.empty())
                    {
                        throw std::runtime_error("error : no project included!");
                    }
                    else
                    {
                        // crea associazione tra step e progetto dichiarato
                        CAXml_Layers *slayer=new CAXml_Layers();
                        if(slayer)
                        {
                            std::string layer_name=conf.conf.layers+step->projects;
                            if(slayer->loadFromXml(layer_name))
                            {
                                LogInfo ("Step %s : create environment variables");
                                LogInfo("Step %s : create jobs by layer :5s",step->name.c_str(),layer_name.c_str() );
                                jobs.push_back(new caJobStep(step,slayer));
                            }
                        }
                    }
                }
            }
        }
        else
        {
            throw std::runtime_error("Cannot load xml file : %s"+conf_file);
        }
    }
    return res;
}

bool cakeManager::reset ()
{
    auto res=false;
    return res;
}


void cakeManager::prepareDefaultEnv(void)
{
    if(!conf.conf.root.empty())
    {
        env->add("ROOT",conf.conf.root);
        env->add("REPO",conf.conf.repo);
        env->add("STORE",conf.conf.store);
        env->add("SOURCES",conf.conf.sources);
        env->add("EDITOR",conf.conf.editor);
        env->add("IMAGES",conf.conf.images);
        env->add("LD_LIBRARY_PATH",conf.conf.ld_library_path);
        env->add("PATH",conf.conf.path);
        env->dump();
    }
    else
    {
        throw std::runtime_error("Invalid conf file: ROOT env must be set!");
    }
}

}