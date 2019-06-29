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


namespace CA
{

cakeManager::cakeManager()
{

}

cakeManager::~cakeManager()
{

}


bool cakeManager::run(const std::string &conf_file)
{
    auto res=false;
    if(!conf_file.empty())
    {
        if(conf.loadFromXml(conf_file))
        {
            LogInfo("build $ROOT=%s ",conf.conf.root.c_str());
            if(conf.defaults.step.empty())
            {
                LogError("No builds step available, please set cake.conf.default.step");
                exit(1);
            }
            else
            {
                LogInfo("%d build steps",conf.defaults.step.size());
                for (auto &it : conf.defaults.step)
                {
                    CAXml_Main_Defaults_Step *step=dynamic_cast<CAXml_Main_Defaults_Step *>(it);
                    LogInfo("Step %s : %s",step->name.c_str(),step->info.c_str() );
                }
            }
        }
    }
    return res;
}

bool cakeManager::reset ()
{
    auto res=false;
    return res;
}

}