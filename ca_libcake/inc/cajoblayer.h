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



class caPrjStatus
    : public IPrjStatus
{
private:
    std::string fullpath;
    std::string fullprojconf;
    std::string layer;
    std::string name;
    void * st;
    std::string next_exec;
    prjPhase phase;
    prjPhaseSource pSource;
    prjPhaseBuild pBuild;
    prjPhasePackage pPackage;
    prjPhaseDeploy  pDeploy;
public:
    caPrjStatus(std::string & _name, std::string & _proj,std::string &_layer):
        name(_name),fullprojconf(_proj),layer(_layer),
        st(nullptr),phase(ST_NONE),pSource(ST_SOURCE_NONE),
        pBuild(ST_BUILD_NONE),pPackage(ST_PACKAGE_NONE),pDeploy(ST_DEPLOY_NONE) {}
    virtual inline std::string & getFullPath() final {return fullpath;}
    virtual inline std::string & getFullProjConf() final {return fullprojconf;}
    virtual inline std::string & getLayer() final {return layer;}
    virtual inline std::string & getName() final { return name; }
    virtual inline void * getXmlStatus() final {return st;}
    virtual inline std::string & getNextExec() final {return next_exec;}
    virtual inline void setNextExec(std::string v) final { next_exec=v;};
    virtual inline prjPhase getMainPhase() final {return phase;}
    virtual inline void setMainPhase(prjPhase _n)
    {
        phase=_n;
    }
    virtual inline prjPhaseSource getPhaseSource()final {return pSource; }
    virtual inline void setPhaseSource(prjPhaseSource _v)
    {
        phase=ST_SOURCE;
        pSource=_v;
    }
    virtual inline void incPhaseSource() final
    {
        unsigned int v=(unsigned int )pSource;
        v++;
        pSource=(prjPhaseSource)v;
    }
    virtual inline prjPhaseBuild getPhaseBuild()final {return pBuild;}
    virtual inline void setPhaseBuild(prjPhaseBuild _v)
    {
        phase=ST_BUILD;
        pBuild=_v;
    }
    virtual inline void incPhaseBuild() final
    {
        unsigned int v=(unsigned int )pBuild;
        v++;
        pBuild=(prjPhaseBuild)v;
    }
    virtual inline prjPhasePackage getPhasePackage()final {return pPackage;}
    virtual inline void setPhasePackage(prjPhasePackage _v)
    {
        phase=ST_PACKAGE;
        pPackage=_v;
    }
    virtual inline void incPhasePackage() final
    {
        unsigned int v=(unsigned int )pPackage;
        v++;
        pPackage=(prjPhasePackage)v;
    }
    virtual inline prjPhaseDeploy  getPhaseDeploy()final {return pDeploy;}
    virtual inline void setPhaseDeploy(prjPhaseDeploy _v)
    {
        phase=ST_DEPLOY;
        pDeploy=_v;
    }
    virtual inline void incPhaseDeploy() final
    {
        unsigned int v=(unsigned int )pDeploy;
        v++;
        pDeploy=(prjPhaseDeploy)v;
    }
    virtual inline void setXmlStatus(void *stnew)
    {
        st=stnew;
    }
    virtual inline void setFullPath(std::string & p)
    {
        fullpath=p;
    }
    virtual void clearAllStatus() final
    {
        phase=ST_NONE;
        pSource=ST_SOURCE_NONE;
        pBuild=ST_BUILD_NONE;
        pPackage=ST_PACKAGE_NONE;
        pDeploy=ST_DEPLOY_NONE;
    }

};


typedef std::map<std::string,IPrjStatus *> statusMap;

class ICAjob_layer
{
public:
    virtual size_t getNumWork(std::list<std::string > & order)=0;
    virtual void   prepareScripts(void)=0;
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
    void prepareProjectScripts(std::string &repo);
    void getNextExec(IPrjStatus *st);
    void setCurrentScript(IPrjStatus *st);
    void setNextStep(IPrjStatus *st);
public:
    caJobLayer(ICAjob_step *js):jobstep(js) {}
    ~caJobLayer();
    inline size_t getNumWork(std::list<std::string > & order)
    {
        return loadLayerStatus(order);
    }
    void   prepareScripts() final;
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