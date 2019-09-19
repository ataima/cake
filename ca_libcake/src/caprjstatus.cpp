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
#include "cacakemanager.h"
#include "calayerconf.h"
#include "cautils.h"
#include "castatusconf.h"
#include "caprjstatus.h"



namespace CA
{

void caPrjStatusUtils::setNextStep(IPrjStatus *st)
{
    if (st)
    {
        switch(st->getMainPhase())
        {
        case ST_COMPLETE:
            break;
        case ST_NONE:
            st->clearAllStatus();
            st->setMainPhase(ST_SOURCE);
            break;
        case ST_SOURCE:
            if(st->getPhaseSource()==ST_SOURCE_POST_SAVE)
            {
                st->setMainPhase(ST_BUILD);
            }
            else
            {
                st->incPhaseSource();
            }
            break;
        case ST_BUILD:
            if(st->getPhaseBuild()==ST_BUILD_POST_INSTALL)
            {
                st->setMainPhase(ST_PACKAGE);
            }
            else
            {
                st->incPhaseBuild();
            }
            break;
        case ST_PACKAGE:
            if(st->getPhasePackage()==ST_PACKAGE_POST)
            {
                st->setMainPhase(ST_DEPLOY);
            }
            else
            {
                st->incPhasePackage();
            }
            break;
        case ST_DEPLOY:
            if(st->getPhaseDeploy()==ST_DEPLOY_POST)
            {
                st->setMainPhase(ST_COMPLETE);
            }
            else
            {
                st->incPhaseDeploy();
            }
            break;
        }
    }
}


void caPrjStatusUtils::getNextExec(IPrjStatus *st)
{
    if (st)
    {
        st->clearAllStatus();
        CAXml_Status *cur = static_cast<CAXml_Status *>(st->getXmlStatus());
        if(cur)
        {
            if(cur->pre_download!="1")
            {
                st->setPhaseSource(ST_SOURCE_PRE_DOWNLOAD);
            }
            else if(cur->download!="1")
            {
                st->setPhaseSource(ST_SOURCE_DOWNLOAD);
            }
            else if(cur->post_download!="1")
            {
                st->setPhaseSource(ST_SOURCE_POST_DOWNLOAD);
            }
            else if(cur->pre_patch!="1")
            {
                st->setPhaseSource(ST_SOURCE_PRE_PATCH);
            }
            else if(cur->patch!="1")
            {
                st->setPhaseSource(ST_SOURCE_PATCH);
            }
            else if(cur->post_patch!="1")
            {
                st->setPhaseSource(ST_SOURCE_POST_PATCH);
            }
            else if(cur->pre_save_source!="1")
            {
                st->setPhaseSource(ST_SOURCE_PRE_SAVE);
            }
            else if(cur->save_source!="1")
            {
                st->setPhaseSource(ST_SOURCE_SAVE);
            }
            else if(cur->post_save_source!="1")
            {
                st->setPhaseSource(ST_SOURCE_POST_SAVE);
            }
            else if(cur->pre_configure!="1")
            {
                st->setPhaseBuild(ST_BUILD_PRE_CONFIGURE);
            }
            else if(cur->configure!="1")
            {
                st->setPhaseBuild(ST_BUILD_CONFIGURE);
            }
            else if(cur->post_configure!="1")
            {
                st->setPhaseBuild(ST_BUILD_POST_CONFIGURE);
            }
            else if(cur->pre_build!="1")
            {
                st->setPhaseBuild(ST_BUILD_PRE_BUILD);
            }
            else if(cur->build!="1")
            {
                st->setPhaseBuild(ST_BUILD_BUILD);
            }
            else if(cur->post_build!="1")
            {
                st->setPhaseBuild(ST_BUILD_POST_BUILD);
            }
            else if(cur->pre_install!="1")
            {
                st->setPhaseBuild(ST_BUILD_PRE_INSTALL);
            }
            else if(cur->install!="1")
            {
                st->setPhaseBuild(ST_BUILD_INSTALL);
            }
            else if(cur->post_install!="1")
            {
                st->setPhaseBuild(ST_BUILD_POST_INSTALL);
            }
            else if(cur->pre_package!="1")
            {
                st->setPhasePackage(ST_PACKAGE_PRE);
            }
            else if(cur->package!="1")
            {
                st->setPhasePackage(ST_PACKAGE_PACKAGE);
            }
            else if(cur->post_package!="1")
            {
                st->setPhasePackage(ST_PACKAGE_POST);
            }
            else if(cur->pre_deploy!="1")
            {
                st->setPhaseDeploy(ST_DEPLOY_PRE);
            }
            else if(cur->deploy!="1")
            {
                st->setPhaseDeploy(ST_DEPLOY_IMAGE);
            }
            else if(cur->post_deploy!="1")
            {
                st->setPhaseDeploy(ST_DEPLOY_POST);
            }
            else
            {
                st->setMainPhase(ST_COMPLETE);
            }
            setCurrentScript(st);
        }
    }
}

void caPrjStatusUtils::setCurrentScript(IPrjStatus *st)
{
    const char * source_script_name[]=
    {
        "",
        "pre_download.sh",
        "download.sh",
        "post_download.sh",
        "pre_patch.sh",
        "patch.sh",
        "post_patch.sh",
        "pre_save.sh",
        "save.sh",
        "post_save.sh",
    };
    const char * build_script_name[]=
    {
        "",
        "pre_configure.sh",
        "configure.sh",
        "post_configure.sh",
        "pre_build.sh",
        "build.sh",
        "post_build.sh",
        "pre_install.sh",
        "install.sh",
        "post_install.sh",
    };
    const char * package_script_name[]=
    {
        "",
        "pre_package.sh",
        "package.sh",
        "post_package.sh",
    };
    const char * deploy_script_name[]=
    {
        "",
        "pre_deploy.sh",
        "deploy.sh",
        "post_deploy.sh",
    };
    if (st)
    {
        st->setNextExec("");
        switch(st->getMainPhase())
        {
        case ST_COMPLETE:
        case ST_NONE:
            break;
        case ST_SOURCE:
            st->setNextExec(source_script_name[st->getPhaseSource()]);
            break;
        case ST_BUILD:
            st->setNextExec(build_script_name[st->getPhaseBuild()]);
            break;
        case ST_PACKAGE:
            st->setNextExec(package_script_name[st->getPhasePackage()]);
            break;
        case ST_DEPLOY:
            st->setNextExec(deploy_script_name[st->getPhaseDeploy()]);
            break;
        }
    }
}


}