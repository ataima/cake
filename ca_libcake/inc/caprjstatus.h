#ifndef CA_PRJ_STATUS_HEADER
#define CA_PRJ_STATUS_HEADER


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
    std::string scriptpath;
    void * st;
    std::string next_exec;
    prjPhase phase;
    prjPhaseSource pSource;
    prjPhaseBuild pBuild;
    prjPhasePackage pPackage;
    prjPhaseDeploy  pDeploy;
    int exec_result;
public:
    caPrjStatus(std::string & _name, std::string & _proj,std::string &_layer):
        name(_name),fullprojconf(_proj),layer(_layer),
        st(nullptr),phase(ST_NONE),pSource(ST_SOURCE_NONE),
        pBuild(ST_BUILD_NONE),pPackage(ST_PACKAGE_NONE),
        exec_result(0),pDeploy(ST_DEPLOY_NONE) {}
    inline std::string & getFullPath() final {return fullpath;}
    inline std::string & getFullProjConf() final {return fullprojconf;}
    inline std::string & getLayer() final {return layer;}
    inline std::string & getName() final { return name; }
    inline void * getXmlStatus() final {return st;}
    inline std::string & getNextExec() final {return next_exec;}
    inline void setNextExec(std::string v) final { next_exec=v;};
    inline int getExecResult() final { return exec_result;}
    inline void setExecResult(int n) final
    {
        exec_result=n;
    }
    inline prjPhase getMainPhase() final {return phase;}
    inline void setMainPhase(prjPhase _n)final
    {
        phase=_n;
    }
    inline prjPhaseSource getPhaseSource()final {return pSource;}
    inline void setPhaseSource(prjPhaseSource _v)final
    {
        phase=ST_SOURCE;
        pSource=_v;
    }
    inline std::string & getPathScript()final {return scriptpath;}
    inline void incPhaseSource() final
    {
        auto v=(unsigned int )pSource;
        v++;
        pSource=(prjPhaseSource)v;
    }
    inline prjPhaseBuild getPhaseBuild()final {return pBuild;}
    inline void setPhaseBuild(prjPhaseBuild _v)final
    {
        phase=ST_BUILD;
        pBuild=_v;
    }
    inline void incPhaseBuild() final
    {
        auto v=(unsigned int )pBuild;
        v++;
        pBuild=(prjPhaseBuild)v;
    }
    inline prjPhasePackage getPhasePackage()final {return pPackage;}
    inline void setPhasePackage(prjPhasePackage _v)final
    {
        phase=ST_PACKAGE;
        pPackage=_v;
    }
    inline void incPhasePackage() final
    {
        auto v=(unsigned int )pPackage;
        v++;
        pPackage=(prjPhasePackage)v;
    }
    inline prjPhaseDeploy  getPhaseDeploy()final {return pDeploy;}
    inline void setPhaseDeploy(prjPhaseDeploy _v)final
    {
        phase=ST_DEPLOY;
        pDeploy=_v;
    }
    inline void incPhaseDeploy() final
    {
        auto v=(unsigned int )pDeploy;
        v++;
        pDeploy=(prjPhaseDeploy)v;
    }
    inline void setXmlStatus(void *stnew)final
    {
        st=stnew;
    }
    inline void setFullPath(std::string & p)final
    {
        fullpath=p;
    }
    inline void setPathScript(std::string & p) final
    {
        scriptpath=p;
    }
    void clearAllStatus() final
    {
        phase=ST_NONE;
        pSource=ST_SOURCE_NONE;
        pBuild=ST_BUILD_NONE;
        pPackage=ST_PACKAGE_NONE;
        pDeploy=ST_DEPLOY_NONE;
    }

};

class caPrjStatusUtils
{
public:
    static void setNextStep(IPrjStatus *st);
    static void getNextExec(IPrjStatus *st);
    static void setCurrentScript(IPrjStatus *st);
    static void save(IPrjStatus *st);

};

}


#endif
