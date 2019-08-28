
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
#include "calogiface.h"
#include "calogger.h"
#include "cacakemanager.h"
#include "calayerconf.h"
#include "cajobstep.h"
#include "cajoblayer.h"
#include "cautils.h"
#include <caconfenv.h>
#include <cstdlib>


namespace CA
{


void caJobLayer::checkLayerStatus()
{
    std::string replaced;
    jobstep->getEnv()->getValue("STATUS",replaced);
    caUtils::checkDirExistOrCreate(replaced);
    std::string layer_name;
    CAXml_Main_Defaults_Step * step= dynamic_cast<CAXml_Main_Defaults_Step *>(jobstep->getStep());
    caUtils::getFileName(step->layer,layer_name);
    caUtils::appendPath(replaced,layer_name);
    caUtils::checkDirExistOrCreate(replaced);
    checkProjectsStatus(replaced,layer_name);
}

void caJobLayer::checkProjectsStatus(std::string & path,std::string & layer_name)
{
    CAXml_Layer *layer = dynamic_cast<CAXml_Layer *>(jobstep->getLayer());
    for(auto prj: layer->include)
    {
        std::string p_status_name = prj+".xml";
        std::string p_status=path;
        caUtils::appendPath(p_status,p_status_name);
        if(caUtils::checkFileExist(p_status))
        {

        }
        else
        {
            LogInfo("%s:Status file  for project %s not available ,create ",
                    layer_name.c_str(),prj.c_str());
        }
    }

}

size_t caJobLayer::getNumWork(jobsList &towork)
{
    int result=0;
    towork.clear();
    checkLayerStatus();
    return towork.size();
}
}