
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
#include "calogiface.h"
#include "cacakemanager.h"
#include "calayerconf.h"
#include "cajobstep.h"
#include <caconfenv.h>
#include <cstdlib>


namespace CA
{

/*
<step>
            <ar>ar</ar>
            <arch>x86_64</arch>
            <as>as</as>
            <asflags/>
            <c_include_path/>
            <cc>gcc</cc>
            <cflags>-O3</cflags>
            <cpath/>
            <cplus_include_path/>
            <cppflags>-O3</cppflags>
            <cross>x86_64-pc-linux-gnu</cross>
            <cxx>g++</cxx>
            <cxxflags>-O3</cxxflags>
            <id>0</id>
            <info>First step to create a gcc native at last version to build all packets</info>
            <ld>ld</ld>
            <ldflags/>
            <libs/>
            <name>build_gcc</name>
            <nm>nm</nm>
            <packages>$ROOT/packages/build_gcc</packages>
            <projects>./project_sted_id_0.xml</projects>
            <step_name>prepare new gcc from source</step_name>
            <strip>strip</strip>
            <user_env id="0" >
                <name>USER_PATH</name>
                <value>$ROOT/images/egg_sysroot/bin:$ROOT/images/egg_sysroot/x86_64-pc-linux-gnu/bin:/bin:/usr/bin</value>
            </user_env>
        </step>
     */


void caJobStep::prepareDefaultEnv(IGetConfEnv  * _env)
{
    env=new caGetConfEnv(_env);
    if(step_conf)
    {
        CAXml_Main_Defaults_Step *step=dynamic_cast<CAXml_Main_Defaults_Step*>(step_conf);
        env->add("AR",step->ar);
        env->add("ARCH",step->arch);
        env->add("AS",step->as);
        env->add("ASFLAGS",step->asflags);
        env->add("C_INCLUDE_PATH",step->c_include_path);
        env->add("CC",step->cc);
        env->add("CFLAGS",step->cflags);
        env->add("CPATH",step->cpath);
        env->add("CPLUS_INCLUDE_PATH",step->cplus_include_path);
        env->add("CPPFLAGS",step->cppflags);
        env->add("CROSS",step->cross);
        env->add("CXX",step->cxx);
        env->add("CXXFLAGS",step->cxxflags);
        env->add("ID",step->id);
        env->add("INFO",step->info);
        env->add("LD",step->ld);
        env->add("LDFLAGS",step->ldflags);
    }
}

//////////////////////////////////////////////////////////////////////////////////
void caJobStepManager::reset()
{
    for (auto job : *this)
    {
        job->reset();
        delete job;
    }
    clear();
}

void caJobStepManager::prepareStep(IGetConfEnv  * _env)
{
    for(auto job: *this)
    {
        if(job)
        {
            job->prepareDefaultEnv(_env);
        }
    }

}

}