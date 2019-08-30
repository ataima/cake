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
    virtual void exec(IGetConfEnv  * _env, prjStatus * pst)=0;
};


class caJobMakeSourceScript
    :public ICAjob_make_script
{
public:
    void exec(IGetConfEnv  * _env, prjStatus * pst) final;
};

class caJobMakeBuildScript
    :public ICAjob_make_script
{
public:
    void exec(IGetConfEnv  * _env, prjStatus * pst) final;
};

class caJobMakePackageScript
    :public ICAjob_make_script
{
public:
    void exec(IGetConfEnv  * _env, prjStatus * pst) final;
};

class caJobMakeDeployScript
    :public ICAjob_make_script
{
public:
    void exec(IGetConfEnv  * _env, prjStatus * pst) final;
};


}

#endif