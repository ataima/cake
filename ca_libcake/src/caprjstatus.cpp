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
#include <unistd.h>


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
                st->incPhaseBuild();
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
                st->incPhasePackage();
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
                st->incPhaseDeploy();
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
    setCurrentScript(st);
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



static void save_source_none(IPrjStatus *st,CAXml_Status *xml)
{
    xml->pre_download="";
    xml->download="";
    xml->post_download="";
    xml->pre_patch="";
    xml->patch="";
    xml->post_patch="";
    xml->pre_save_source="";
    xml->save_source="";
    xml->post_save_source="";
    //
    xml->pre_configure="";
    xml->configure="";
    xml->post_configure="";
    xml->pre_build="";
    xml->build="";
    xml->post_build="";
    xml->pre_install="";
    xml->install="";
    xml->post_install="";
    //
    xml->pre_package="";
    xml->package="";
    xml->post_package="";
    //
    xml->pre_deploy="";
    xml->deploy="";
    xml->post_deploy="";
}

static void save_source_status(IPrjStatus *st,CAXml_Status *xml)
{
    if(st!=nullptr && xml!=nullptr)
    {
        switch(st->getPhaseSource())
        {
        case ST_SOURCE_NONE:
            xml->pre_download="";
            xml->download="";
            xml->post_download="";
            xml->pre_patch="";
            xml->patch="";
            xml->post_patch="";
            xml->pre_save_source="";
            xml->save_source="";
            xml->post_save_source="";
            break;
        case ST_SOURCE_PRE_DOWNLOAD:
            xml->pre_download="1";
            break;
        case ST_SOURCE_DOWNLOAD:
            xml->download="1";
            break;
        case ST_SOURCE_POST_DOWNLOAD:
            xml->post_download="1";
            break;
        case ST_SOURCE_PRE_PATCH:
            xml->pre_patch="1";
            break;
        case ST_SOURCE_PATCH:
            xml->patch="1";
            break;
        case ST_SOURCE_POST_PATCH:
            xml->post_patch="1";
            break;
        case ST_SOURCE_PRE_SAVE:
            xml->pre_save_source="1";
            break;
        case ST_SOURCE_SAVE:
            xml->save_source="1";
            break;
        case ST_SOURCE_POST_SAVE:
            xml->post_save_source="1";
            break;
        }
    }
}



static void save_build_status(IPrjStatus *st,CAXml_Status *xml)
{
    if(st!=nullptr && xml!=nullptr)
    {
        switch(st->getPhaseBuild())
        {
        case ST_BUILD_NONE:
            xml->pre_configure="";
            xml->configure="";
            xml->post_configure="";
            xml->pre_build="";
            xml->build="";
            xml->post_build="";
            xml->pre_install="";
            xml->install="";
            xml->post_install="";
            break;
        case ST_BUILD_PRE_CONFIGURE:
            xml->pre_configure="1";
            break;
        case ST_BUILD_CONFIGURE:
            xml->configure="1";
            break;
        case ST_BUILD_POST_CONFIGURE:
            xml->post_configure="1";
            break;
        case ST_BUILD_PRE_BUILD:
            xml->pre_build="1";
            break;
        case ST_BUILD_BUILD:
            xml->build="1";
            break;
        case ST_BUILD_POST_BUILD:
            xml->post_build="1";
            break;
        case ST_BUILD_PRE_INSTALL:
            xml->pre_install="1";
            break;
        case ST_BUILD_INSTALL:
            xml->install="1";
            break;
        case ST_BUILD_POST_INSTALL:
            xml->post_install="1";
            break;
        }
    }
}


static void save_package_status(IPrjStatus *st,CAXml_Status *xml)
{
    if(st!=nullptr && xml!=nullptr)
    {
        switch(st->getPhasePackage())
        {
        case ST_PACKAGE_NONE:
            xml->pre_package="";
            xml->package="";
            xml->post_package="";
            break;
        case ST_PACKAGE_PRE:
            xml->pre_package="1";
            break;
        case ST_PACKAGE_PACKAGE:
            xml->package="1";
            break;
        case ST_PACKAGE_POST:
            xml->post_package="1";
            break;
        }
    }
}


static void save_deploy_status(IPrjStatus *st,CAXml_Status *xml)
{
    if(st!=nullptr && xml!=nullptr)
    {
        switch(st->getPhaseDeploy())
        {
        case ST_DEPLOY_NONE:
            xml->pre_deploy="";
            xml->deploy="";
            xml->post_deploy="";
            break;
        case ST_DEPLOY_PRE:
            xml->pre_deploy="1";
            break;
        case ST_DEPLOY_IMAGE:
            xml->deploy="1";
            break;
        case ST_DEPLOY_POST:
            xml->post_deploy="1";
            break;
        }
    }
}


void caPrjStatusUtils::save(IPrjStatus *st)
{
    if (st)
    {
        CAXml_Status *cur = static_cast<CAXml_Status *>(st->getXmlStatus());
        if(cur)
        {
            switch(st->getMainPhase())
            {
            case ST_COMPLETE:
                break;
            case ST_NONE:
            {
                save_source_none(st,cur);
            }
            break;
            case ST_SOURCE:
            {
                save_source_status(st,cur);
            }
            break;
            case ST_BUILD:
            {
                save_build_status(st,cur);
            }
            break;
            case ST_PACKAGE:
            {
                save_package_status(st,cur);
            }
            break;
            case ST_DEPLOY:
            {
                save_deploy_status(st,cur);
            }
            break;
            }
            /*
            try
            {*/
            const char *filename=st->getFullPath().c_str();
            std::fstream ofs(filename, std::ios_base::out);
            if(ofs.is_open())
            {
                cur->toString(ofs);
                ofs.flush();
                ofs.close();
            }
            /*
            }
            catch(...)
            {
            std::string msg="STATUS : Cannot write on "+st->getFullPath();
            std::runtime_error e(msg.c_str());
            throw(e);
            }
            */
        }
    }
}

}