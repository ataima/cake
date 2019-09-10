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

namespace CA
{


class ICAjob_make_script
{
public:
    virtual void create(ICAjob_layer *layer ,IGetConfEnv  * _env, IPrjStatus *pst)=0;
};

typedef bool (*funcCreateScript)(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname) ;


class caJobMakeBase
    :public ICAjob_make_script
{
public:
    static bool checkStatusScript(ICAjob_layer *layer ,IGetConfEnv  * env, IPrjStatus *pst,
                                  std::string & scriptname);
    static bool createScriptPhase(ICAjob_layer *layer ,IGetConfEnv  * env, IPrjStatus *pst,
                                  const funcCreateScript funcs[], size_t off);
    static void createScriptHeader(std::ofstream &of,IGetConfEnv  * env);
};


class caJobMakeSourceScript
    :public caJobMakeBase
{
public:
    void create(ICAjob_layer *layer ,IGetConfEnv  * _env, IPrjStatus *pst) final;
    static bool createPreDownload(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createDownload(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createPostDownload(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createPrePatch(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createPatch(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createPostPatch(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createPreSource(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createSource(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createPostSource(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
};

class caJobMakeBuildScript
    :public caJobMakeBase
{
public:
    void create(ICAjob_layer *layer ,IGetConfEnv  * _env, IPrjStatus *pst) final;
    static bool createPreConfigure(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createConfigure(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createPostConfigure(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createPreBuild(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createBuild(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createPostBuild(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createPreInstall(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createInstall(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createPostInstall(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
};

class caJobMakePackageScript
    :public caJobMakeBase
{
public:
    void create(ICAjob_layer *layer ,IGetConfEnv  * _env, IPrjStatus *pst) final;
    static bool createPrePackage(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createPackage(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createPostPackage(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
};

class caJobMakeDeployScript
    :public caJobMakeBase
{
public:
    void create(ICAjob_layer *layer ,IGetConfEnv  * _env, IPrjStatus *pst) final;
    static bool createPreDeploy(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createImage(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
    static bool createPostDeploy(IGetConfEnv  * env, IPrjStatus *pst,std::string & scriptname);
};


}

#endif