#ifndef CA_JOB_LAYER_HEADER
#define CA_JOB_LAYER_HEADER


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
#include "cajobstep.h"

namespace CA
{

typedef std::list<std::string> jobsList;

class ICAjob_layer
{
public:
    virtual int getNumWork(jobsList &towork)=0;

};




class caJobLayer
    :public ICAjob_layer
{
protected:
    ICAjob_step *jobstep;
public:
    caJobLayer(ICAjob_step *js):jobstep(js){}
    int getNumWork(jobsList &towork) final;
};





}

#endif // CA_JOB_LAYER_HEADER