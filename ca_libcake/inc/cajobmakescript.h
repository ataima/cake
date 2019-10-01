#ifndef CA_JOB_MAKE_SCRIPT
#define CA_JOB_MAKE_SCRIPT


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
#include <caprojectconf.h>


namespace CA
{


class ICAjob_make_script
{
public:
    virtual void create(ICAXml_Project *prj,ICAjob_layer *layer ,IGetConfEnv  * _env, IPrjStatus *pst)=0;
};

typedef bool (*funcCreateScript)(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname) ;


class caJobMakeBase
    :public ICAjob_make_script
{
public:
    static bool checkStatusScript(ICAjob_layer *layer ,IGetConfEnv  * env, IPrjStatus *pst,
                                  std::string & scriptname);
    static bool createScriptPhase(ICAXml_Project *prj,ICAjob_layer *layer ,IGetConfEnv  * env, IPrjStatus *pst,
                                  const funcCreateScript funcs[], size_t off);
    static void createScriptHeader(std::ofstream &of,IGetConfEnv  * env,envSet &subset);
    static bool checkExistCustomScript(ICAjob_layer *layer ,IGetConfEnv  * env,
                                       IPrjStatus *pst,std::string & scriptToCreate);

};


class caJobMakeSourceScript
    :public caJobMakeBase
{
private:
    static void createDefaultSourceHeader(std::ofstream & of,IGetConfEnv  * env, IPrjStatus *pst);
public:
    void create(ICAXml_Project *prj,ICAjob_layer *layer ,IGetConfEnv  * _env, IPrjStatus *pst) final;
    static bool createPreDownload(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createDownload(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createPostDownload(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createPrePatch(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createPatch(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createPostPatch(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createPreSource(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createSource(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createPostSource(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
};

class caJobMakeBuildScript
    :public caJobMakeBase
{
public:
    void create(ICAXml_Project *prj,ICAjob_layer *layer ,IGetConfEnv  * _env, IPrjStatus *pst) final;
    static bool createPreConfigure(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createConfigure(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createPostConfigure(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createPreBuild(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createBuild(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createPostBuild(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createPreInstall(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createInstall(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createPostInstall(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
};

class caJobMakePackageScript
    :public caJobMakeBase
{
public:
    void create(ICAXml_Project *prj,ICAjob_layer *layer ,IGetConfEnv  * _env, IPrjStatus *pst) final;
    static bool createPrePackage(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createPackage(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createPostPackage(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
};

class caJobMakeDeployScript
    :public caJobMakeBase
{
public:
    void create(ICAXml_Project *prj,ICAjob_layer *layer ,IGetConfEnv  * _env, IPrjStatus *pst) final;
    static bool createPreDeploy(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createImage(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createPostDeploy(ICAXml_Project *prj,IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
};


}

#endif