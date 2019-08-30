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
#include "cainterfaces.h"
#include "camainconf.h"
#include "calayerconf.h"
#include "castatusconf.h"

namespace CA
{


typedef enum tag_project_phase
{
    ST_NONE,
    ST_SOURCE,
    ST_BUILD,
    ST_PACKAGE,
    ST_DEPLOY,
    ST_COMPLETE
} prjPhase;

typedef struct tag_pos_status
{
    std::string fullpath;
    std::string fullprojconf;
    std::string name;
    ICAXml_Status * st;
    std::string next_exec;
    prjPhase phase;
} prjStatus;


typedef std::map<std::string,prjStatus * > statusMap;

class ICAjob_layer
{
public:
    virtual size_t getNumWork(std::list<std::string > & order)=0;
    virtual statusMap* getStatusMap()=0;
    virtual std::string & getName()=0;

};

class ICAjob_step;


class caJobLayer
    :public ICAjob_layer
{
protected:
    ICAjob_step *jobstep;
    statusMap projects_status;
    std::string layer_name;
    size_t loadLayerStatus(std::list<std::string > & order);
    size_t loadProjectsStatus(std::list<std::string > & order,std::string & path,
                              std::string & repo, std::string & layer_name);
    void getNextExec(prjStatus *st);
public:
    caJobLayer(ICAjob_step *js):jobstep(js) {}
    ~caJobLayer();
    inline size_t getNumWork(std::list<std::string > & order)
    {
        return loadLayerStatus(order);
    }
    inline  statusMap* getStatusMap()
    {
        return &projects_status;
    }
    inline std::string & getName()
    {
        return layer_name;
    };
};





}

#endif // CA_JOB_LAYER_HEADER