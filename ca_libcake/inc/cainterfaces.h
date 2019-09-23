#ifndef CA_INTERFACES
#define CA_INTERFACES

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



#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <thread>
#include <set>
#include <fstream>
#include <string>



#ifndef _MSC_VER
#pragma pack(0)
#endif
//////////////////////////////////////////////////////

#define _MORE_DEBUG 1

#if _MORE_DEBUG

inline void  int_sys_throw(std::string & msg,const char * file, int line )
{
    std::stringstream ss;
    ss<<std::endl<<"At file : "<<file<<std::endl;
    ss<<"At line : "<<line<<std::endl;
    ss<<"Exception :" <<msg;
    throw std::runtime_error(ss.str());
}
#define sys_throw(msg) int_sys_throw(msg,__FILE__,__LINE__)

#else
inline void int_sys_throw(std::string & msg,const char * file, int line )
{
    throw std::runtime_error(msg);
}
#define sys_throw(msg) int_sys_throw(msg)

#endif





namespace CA
{


#define  BUFFLENGTH  512

#ifdef _DOUBLE_UNICODE
typedef  char32_t     _cbt;
#else
#ifdef _UNICODE
typedef  char16_t     _cbt;
#else
typedef  char     _cbt;
#endif
#endif


typedef enum tag_flg_index
{
    f_help,
    f_verbose,
    f_debug,
    f_force_generate,
    f_last_flags
} availOption;


typedef enum tag_project_phase
{
    ST_NONE,
    ST_SOURCE,
    ST_BUILD,
    ST_PACKAGE,
    ST_DEPLOY,
    ST_COMPLETE
} prjPhase;

typedef enum tag_project_phase_source
{
    ST_SOURCE_NONE,
    ST_SOURCE_PRE_DOWNLOAD,
    ST_SOURCE_DOWNLOAD,
    ST_SOURCE_POST_DOWNLOAD,
    ST_SOURCE_PRE_PATCH,
    ST_SOURCE_PATCH,
    ST_SOURCE_POST_PATCH,
    ST_SOURCE_PRE_SAVE,
    ST_SOURCE_SAVE,
    ST_SOURCE_POST_SAVE,
} prjPhaseSource;


typedef enum tag_project_phase_build
{
    ST_BUILD_NONE,
    ST_BUILD_PRE_CONFIGURE,
    ST_BUILD_CONFIGURE,
    ST_BUILD_POST_CONFIGURE,
    ST_BUILD_PRE_BUILD,
    ST_BUILD_BUILD,
    ST_BUILD_POST_BUILD,
    ST_BUILD_PRE_INSTALL,
    ST_BUILD_INSTALL,
    ST_BUILD_POST_INSTALL,
} prjPhaseBuild;


typedef enum tag_project_phase_package
{
    ST_PACKAGE_NONE,
    ST_PACKAGE_PRE,
    ST_PACKAGE_PACKAGE,
    ST_PACKAGE_POST,
} prjPhasePackage;


typedef enum tag_project_phase_deploy
{
    ST_DEPLOY_NONE,
    ST_DEPLOY_PRE,
    ST_DEPLOY_IMAGE,
    ST_DEPLOY_POST,
} prjPhaseDeploy;

typedef struct tag_phase_max_task
{
    int max_source_task;
    int max_build_task;
    int max_package_task;
    int max_deploy_task;
} phaseMaxTask;




class IOptionArgvManager;

typedef void (*helpFunctor)(IOptionArgvManager *manager);


class IOptionArgv
{
public:
    typedef enum tag_ioption_argv
    {
        optARGV_NONE,
        optARGV_BOOL,
        optARGV_STRING,
        optARGV_INT
    } optionArgvType;
public:
    virtual ~IOptionArgv()=default;
    virtual const _cbt * getName()=0;
    virtual void parse(const char * argv[],size_t size,size_t & index)=0;
    virtual const _cbt * getStringValue()=0;
    virtual size_t getIntValue()=0;
    virtual bool  isSelect()=0;
    virtual const helpFunctor getHelpFunctor()=0;
    virtual size_t getOffset()=0;
    static  bool  isOption(const _cbt *arg);
};





typedef std::list<std::string> stringList;
typedef std::map<const std::string ,CA::IOptionArgv *> optionMap;
typedef std::vector<CA::IOptionArgv *> optionDir;

class IOptionArgvManager
{
protected:
    static IOptionArgvManager *instance;
public:
    virtual ~IOptionArgvManager()
    {
        instance =nullptr;
    }
    virtual void Parse(const char * argv[],size_t size)=0;
    virtual bool saveAsXml(const _cbt * filename)=0;
    static IOptionArgvManager * getInstance()
    {
        return instance;
    }
    static bool checkOption(size_t offset)
    {
        if(instance)
        {
            return instance->getOptionsArray().at(offset)->isSelect();
        }
        return false;
    }
    virtual void addOption(IOptionArgv * reqOpt)=0;
    virtual const optionMap & getOptionsMap()=0;
    virtual const optionDir & getOptionsArray()=0;
    virtual const stringList & getArgs()=0;
    virtual IOptionArgv * getOption(size_t)=0;
    virtual IOptionArgv * getOption(const std::string & opt)=0;
};



class ICake
{
public:
    virtual bool run(const std::string & conf_file)=0;
    virtual void reset()=0;
};



class IMainAppExecutor
{
public:
    virtual ~IMainAppExecutor()=default;
    virtual bool init(const char * argv[],size_t size)=0;
    virtual bool execute()=0;
};


typedef std::map<std::string ,std::string > envMap;


class IGetConfEnv
{
public:
    virtual ~IGetConfEnv()=default;
    virtual bool add(const char *key,std::string value)=0;
    virtual bool add(envMap & map)=0;
    virtual bool getValue(const char * key ,std::string & out )=0;
    virtual void dump(const char *envinfo)=0;
    virtual void append( IGetConfEnv * root)=0;
    virtual envMap & getMap()=0;
    virtual void addEnvToScript(std::ofstream & of)=0;
};


class IPrjStatus
{
public:
    virtual std::string & getFullPath()=0;
    virtual void setFullPath(std::string & p)=0;
    virtual std::string & getFullProjConf()=0;
    virtual std::string & getLayer()=0;
    virtual std::string & getName()=0;
    virtual void * getXmlStatus()=0;
    virtual void setXmlStatus(void *stnew)=0;
    virtual std::string & getNextExec()=0;
    virtual void setNextExec(std::string v)=0;
    virtual prjPhase getMainPhase()=0;
    virtual void setMainPhase(prjPhase _n)=0;
    virtual prjPhaseSource getPhaseSource()=0;
    virtual void setPhaseSource(prjPhaseSource _v)=0;
    virtual void incPhaseSource()=0;
    virtual prjPhaseBuild getPhaseBuild()=0;
    virtual void setPhaseBuild(prjPhaseBuild _v)=0;
    virtual void incPhaseBuild()=0;
    virtual prjPhasePackage getPhasePackage()=0;
    virtual void setPhasePackage(prjPhasePackage _v)=0;
    virtual void incPhasePackage()=0;
    virtual prjPhaseDeploy  getPhaseDeploy()=0;
    virtual void setPhaseDeploy(prjPhaseDeploy _v)=0;
    virtual void incPhaseDeploy()=0;
    virtual void clearAllStatus()=0;
    virtual std::string & getPathScript()=0;
    virtual void setPathScript(std::string & p)=0;
    virtual int  getExecResult()=0;
    virtual void setExecResult(int n)=0;
};


typedef std::vector<IPrjStatus *>  prjStatusArray;


class IScheduler
{
public:
    virtual void addExec(IPrjStatus  *status )=0;
    virtual int  doExec()=0;
    virtual bool empty()=0;
    virtual size_t appendJobs(IScheduler * prevJobs)=0;
    virtual size_t removeCompleted()=0;
    virtual prjPhase getPhase()=0;
    virtual     prjStatusArray & getCurrentWorks()=0;
};


class ISchedulerManager
{
private:
    static ISchedulerManager *instance;
public:
    virtual ~ISchedulerManager()
    {
        if(instance)
        {
            delete instance;
        }
        instance =nullptr;
    }
    static ISchedulerManager * getInstance();
    static void  setInstance(ISchedulerManager *_mng);
    virtual void addExec(IPrjStatus *status)=0;
    virtual bool doExec()=0;

};



}  // namespace CA


#endif // CAINTERFACES

