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
#include "cainterfaces.h"
#include "caphaseutils.h"

#include "caminiXml.h"
#include "calcfxml.h"
#include "calayerconf.h"


namespace CA
{
const char *  caPhaseUtils::mainPhaseToCStr(prjPhase phase)
{
    const char *pmsg[]=
    {
        "ST_NONE",
        "ST_SOURCE",
        "ST_BUILD",
        "ST_PACKAGE",
        "ST_DEPLOY",
        "ST_COMPLETE"
    };
    if((size_t)phase > (size_t)ST_COMPLETE)return nullptr;
    return pmsg[(size_t)phase];
}

bool caPhaseUtils::setMaxTask(void *ptr,phaseMaxTask &mt)
{
    auto res=false;
    if(ptr!=nullptr)
    {
        CAXml_Layer * ll=static_cast<CAXml_Layer*>(ptr);
        if(ll!=nullptr)
        {
            mt.max_source_task=::atol(ll->maxtask.source.c_str());
            if(mt.max_source_task==0)mt.max_source_task=1;
            mt.max_build_task=::atol(ll->maxtask.build.c_str());
            if(mt.max_build_task==0)mt.max_build_task=1;
            mt.max_package_task=::atol(ll->maxtask.package.c_str());
            if(mt.max_package_task==0)mt.max_package_task=1;
            mt.max_deploy_task=::atol(ll->maxtask.deploy.c_str());
            if(mt.max_deploy_task==0)mt.max_deploy_task=1;
            res=true;
        }
    }
    return res;
}

int caPhaseUtils::getPhaseMaxThread(prjPhase phase,phaseMaxTask & max_thread)
{
    int res=1;
    switch(phase)
    {
    case ST_SOURCE:
        res=max_thread.max_source_task;
        break;
    case ST_BUILD:
        res=max_thread.max_build_task;
        break;
    case ST_PACKAGE:
        res=max_thread.max_package_task;
        break;
    case ST_DEPLOY:
        res=max_thread.max_deploy_task;
        break;
    default:
        break;
    }
    return res;
}

}