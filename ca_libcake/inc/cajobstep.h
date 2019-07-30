#ifndef CA_JOB_STEP_HEADER
#define CA_JOB_STEP_HEADER


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

#include "camainconf.h"
#include "calayerconf.h"


namespace CA {


class ICAjob_step
{
public:
    virtual ICAXml_Main_Defaults_Step  * getStepConf()=0;
    virtual ICAXml_Layers *getLayersConf()=0;
};


class caJobStep
 :public ICAjob_step
 {
     protected:
    ICAXml_Main_Defaults_Step  *step_conf;
    ICAXml_Layers *layers_conf;
    public:
    caJobStep(ICAXml_Main_Defaults_Step  *_step_conf,ICAXml_Layers *_layers_conf)
        :step_conf(_step_conf),layers_conf(_layers_conf){}
    inline ICAXml_Main_Defaults_Step  *getStepConf()final{return step_conf;}
    inline ICAXml_Layers  *getLayersConf()final{return layers_conf;}
 };

}

#endif // CA_JOB_STEP_HEADER