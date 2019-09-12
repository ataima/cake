
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

#include "caminiXml.h"
#include "calcfxml.h"
#include "camainconf.h"

const CA::_cbt *ICAXml_Main_Defaults_Step_User_env::caKEY_NAME = "name";
const CA::_cbt *ICAXml_Main_Defaults_Step_User_env::caKEY_VALUE = "value";
const CA::_cbt *ICAXml_Main_Defaults_Step_User_env::mName="user_env";


CAXml_Main_Defaults_Step_User_env::CAXml_Main_Defaults_Step_User_env(){
    predef.push_back(CA::xmlNodeSpec( caKEY_NAME,"main.defaults.step.user_env.name",&name));
    predef.push_back(CA::xmlNodeSpec( caKEY_VALUE,"main.defaults.step.user_env.value",&value));
}


const CA::_cbt *ICAXml_Main_Defaults_Step::caKEY_AR = "ar";
const CA::_cbt *ICAXml_Main_Defaults_Step::caKEY_ARCH = "arch";
const CA::_cbt *ICAXml_Main_Defaults_Step::caKEY_AS = "as";
const CA::_cbt *ICAXml_Main_Defaults_Step::caKEY_ASFLAGS = "asflags";
const CA::_cbt *ICAXml_Main_Defaults_Step::caKEY_C_INCLUDE_PATH = "c_include_path";
const CA::_cbt *ICAXml_Main_Defaults_Step::caKEY_CC = "cc";
const CA::_cbt *ICAXml_Main_Defaults_Step::caKEY_CFLAGS = "cflags";
const CA::_cbt *ICAXml_Main_Defaults_Step::caKEY_CPATH = "cpath";
const CA::_cbt *ICAXml_Main_Defaults_Step::caKEY_CPLUS_INCLUDE_PATH = "cplus_include_path";
const CA::_cbt *ICAXml_Main_Defaults_Step::caKEY_CPPFLAGS = "cppflags";
const CA::_cbt *ICAXml_Main_Defaults_Step::caKEY_CROSS = "cross";
const CA::_cbt *ICAXml_Main_Defaults_Step::caKEY_CXX = "cxx";
const CA::_cbt *ICAXml_Main_Defaults_Step::caKEY_CXXFLAGS = "cxxflags";
const CA::_cbt *ICAXml_Main_Defaults_Step::caKEY_ENABLE = "enable";
const CA::_cbt *ICAXml_Main_Defaults_Step::caKEY_ID = "id";
const CA::_cbt *ICAXml_Main_Defaults_Step::caKEY_INFO = "info";
const CA::_cbt *ICAXml_Main_Defaults_Step::caKEY_LAYER = "layer";
const CA::_cbt *ICAXml_Main_Defaults_Step::caKEY_LD = "ld";
const CA::_cbt *ICAXml_Main_Defaults_Step::caKEY_LDFLAGS = "ldflags";
const CA::_cbt *ICAXml_Main_Defaults_Step::caKEY_LIBS = "libs";
const CA::_cbt *ICAXml_Main_Defaults_Step::caKEY_NAME = "name";
const CA::_cbt *ICAXml_Main_Defaults_Step::caKEY_NM = "nm";
const CA::_cbt *ICAXml_Main_Defaults_Step::caKEY_PACKAGES = "packages";
const CA::_cbt *ICAXml_Main_Defaults_Step::caKEY_STRIP = "strip";
const CA::_cbt *ICAXml_Main_Defaults_Step::caKEY_USER_ENV = "user_env";
const CA::_cbt *ICAXml_Main_Defaults_Step::mName="step";


CAXml_Main_Defaults_Step::CAXml_Main_Defaults_Step(){
    predef.push_back(CA::xmlNodeSpec( caKEY_AR,"main.defaults.step.ar",&ar));
    predef.push_back(CA::xmlNodeSpec( caKEY_ARCH,"main.defaults.step.arch",&arch));
    predef.push_back(CA::xmlNodeSpec( caKEY_AS,"main.defaults.step.as",&as));
    predef.push_back(CA::xmlNodeSpec( caKEY_ASFLAGS,"main.defaults.step.asflags",&asflags));
    predef.push_back(CA::xmlNodeSpec( caKEY_C_INCLUDE_PATH,"main.defaults.step.c_include_path",&c_include_path));
    predef.push_back(CA::xmlNodeSpec( caKEY_CC,"main.defaults.step.cc",&cc));
    predef.push_back(CA::xmlNodeSpec( caKEY_CFLAGS,"main.defaults.step.cflags",&cflags));
    predef.push_back(CA::xmlNodeSpec( caKEY_CPATH,"main.defaults.step.cpath",&cpath));
    predef.push_back(CA::xmlNodeSpec( caKEY_CPLUS_INCLUDE_PATH,"main.defaults.step.cplus_include_path",&cplus_include_path));
    predef.push_back(CA::xmlNodeSpec( caKEY_CPPFLAGS,"main.defaults.step.cppflags",&cppflags));
    predef.push_back(CA::xmlNodeSpec( caKEY_CROSS,"main.defaults.step.cross",&cross));
    predef.push_back(CA::xmlNodeSpec( caKEY_CXX,"main.defaults.step.cxx",&cxx));
    predef.push_back(CA::xmlNodeSpec( caKEY_CXXFLAGS,"main.defaults.step.cxxflags",&cxxflags));
    predef.push_back(CA::xmlNodeSpec( caKEY_ENABLE,"main.defaults.step.enable",&enable));
    predef.push_back(CA::xmlNodeSpec( caKEY_ID,"main.defaults.step.id",&id));
    predef.push_back(CA::xmlNodeSpec( caKEY_INFO,"main.defaults.step.info",&info));
    predef.push_back(CA::xmlNodeSpec( caKEY_LAYER,"main.defaults.step.layer",&layer));
    predef.push_back(CA::xmlNodeSpec( caKEY_LD,"main.defaults.step.ld",&ld));
    predef.push_back(CA::xmlNodeSpec( caKEY_LDFLAGS,"main.defaults.step.ldflags",&ldflags));
    predef.push_back(CA::xmlNodeSpec( caKEY_LIBS,"main.defaults.step.libs",&libs));
    predef.push_back(CA::xmlNodeSpec( caKEY_NAME,"main.defaults.step.name",&name));
    predef.push_back(CA::xmlNodeSpec( caKEY_NM,"main.defaults.step.nm",&nm));
    predef.push_back(CA::xmlNodeSpec( caKEY_PACKAGES,"main.defaults.step.packages",&packages));
    predef.push_back(CA::xmlNodeSpec( caKEY_STRIP,"main.defaults.step.strip",&strip));
    predef.push_back(CA::xmlNodeSpec( caKEY_USER_ENV,"main.defaults.step.user_env",&user_env,&user_env_ref_clonable_option));
}


const CA::_cbt *ICAXml_Main_Defaults::caKEY_STEP = "step";
const CA::_cbt *ICAXml_Main_Defaults::mName="defaults";


CAXml_Main_Defaults::CAXml_Main_Defaults(){
    predef.push_back(CA::xmlNodeSpec( caKEY_STEP,"main.defaults.step",&step,&step_ref_clonable));
}


const CA::_cbt *ICAXml_Main_Conf::caKEY_BUILD = "build";
const CA::_cbt *ICAXml_Main_Conf::caKEY_IMAGES = "images";
const CA::_cbt *ICAXml_Main_Conf::caKEY_LD_LIBRARY_PATH = "ld_library_path";
const CA::_cbt *ICAXml_Main_Conf::caKEY_LOGS = "logs";
const CA::_cbt *ICAXml_Main_Conf::caKEY_PATH = "path";
const CA::_cbt *ICAXml_Main_Conf::caKEY_ROOT = "root";
const CA::_cbt *ICAXml_Main_Conf::caKEY_SCRIPTS = "scripts";
const CA::_cbt *ICAXml_Main_Conf::caKEY_SOURCES = "sources";
const CA::_cbt *ICAXml_Main_Conf::caKEY_STATUS = "status";
const CA::_cbt *ICAXml_Main_Conf::caKEY_STORE = "store";
const CA::_cbt *ICAXml_Main_Conf::mName="conf";


CAXml_Main_Conf::CAXml_Main_Conf(){
    predef.push_back(CA::xmlNodeSpec( caKEY_BUILD,"main.conf.build",&build));
    predef.push_back(CA::xmlNodeSpec( caKEY_IMAGES,"main.conf.images",&images));
    predef.push_back(CA::xmlNodeSpec( caKEY_LD_LIBRARY_PATH,"main.conf.ld_library_path",&ld_library_path));
    predef.push_back(CA::xmlNodeSpec( caKEY_LOGS,"main.conf.logs",&logs));
    predef.push_back(CA::xmlNodeSpec( caKEY_PATH,"main.conf.path",&path));
    predef.push_back(CA::xmlNodeSpec( caKEY_ROOT,"main.conf.root",&root));
    predef.push_back(CA::xmlNodeSpec( caKEY_SCRIPTS,"main.conf.scripts",&scripts));
    predef.push_back(CA::xmlNodeSpec( caKEY_SOURCES,"main.conf.sources",&sources));
    predef.push_back(CA::xmlNodeSpec( caKEY_STATUS,"main.conf.status",&status));
    predef.push_back(CA::xmlNodeSpec( caKEY_STORE,"main.conf.store",&store));
}


const CA::_cbt *ICAXml_Main::caKEY_CONF = "conf";
const CA::_cbt *ICAXml_Main::caKEY_DEFAULTS = "defaults";
const CA::_cbt *ICAXml_Main::mName="main";


CAXml_Main::CAXml_Main(){
    predef.push_back(CA::xmlNodeSpec( caKEY_CONF,"main.conf",&conf.node_internal_value,&conf));
    predef.push_back(CA::xmlNodeSpec( caKEY_DEFAULTS,"main.defaults",&defaults.node_internal_value,&defaults));
}


bool CAXml_Main::loadFromXml(std::string filename){
bool res=false;
CA::IXmlNode *root=CA::IXmlNode::getNewNode();
if(root->load(filename)){
    loadFromXml(root);
    res=true;
   }
delete root;
return res;
}

