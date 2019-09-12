
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
#include "castatusconf.h"

const CA::_cbt *ICAXml_Status::caKEY_BUILD = "build";
const CA::_cbt *ICAXml_Status::caKEY_CONFIGURE = "configure";
const CA::_cbt *ICAXml_Status::caKEY_DEPLOY = "deploy";
const CA::_cbt *ICAXml_Status::caKEY_DOWNLOAD = "download";
const CA::_cbt *ICAXml_Status::caKEY_INSTALL = "install";
const CA::_cbt *ICAXml_Status::caKEY_PACKAGE = "package";
const CA::_cbt *ICAXml_Status::caKEY_PATCH = "patch";
const CA::_cbt *ICAXml_Status::caKEY_POST_BUILD = "post_build";
const CA::_cbt *ICAXml_Status::caKEY_POST_CONFIGURE = "post_configure";
const CA::_cbt *ICAXml_Status::caKEY_POST_DEPLOY = "post_deploy";
const CA::_cbt *ICAXml_Status::caKEY_POST_DOWNLOAD = "post_download";
const CA::_cbt *ICAXml_Status::caKEY_POST_INSTALL = "post_install";
const CA::_cbt *ICAXml_Status::caKEY_POST_PACKAGE = "post_package";
const CA::_cbt *ICAXml_Status::caKEY_POST_PATCH = "post_patch";
const CA::_cbt *ICAXml_Status::caKEY_POST_SAVE_SOURCE = "post_save_source";
const CA::_cbt *ICAXml_Status::caKEY_PRE_BUILD = "pre_build";
const CA::_cbt *ICAXml_Status::caKEY_PRE_CONFIGURE = "pre_configure";
const CA::_cbt *ICAXml_Status::caKEY_PRE_DEPLOY = "pre_deploy";
const CA::_cbt *ICAXml_Status::caKEY_PRE_DOWNLOAD = "pre_download";
const CA::_cbt *ICAXml_Status::caKEY_PRE_INSTALL = "pre_install";
const CA::_cbt *ICAXml_Status::caKEY_PRE_PACKAGE = "pre_package";
const CA::_cbt *ICAXml_Status::caKEY_PRE_PATCH = "pre_patch";
const CA::_cbt *ICAXml_Status::caKEY_PRE_SAVE_SOURCE = "pre_save_source";
const CA::_cbt *ICAXml_Status::caKEY_SAVE_SOURCE = "save_source";
const CA::_cbt *ICAXml_Status::mName="status";


CAXml_Status::CAXml_Status(){
    predef.push_back(CA::xmlNodeSpec( caKEY_BUILD,"status.build",&build));
    predef.push_back(CA::xmlNodeSpec( caKEY_CONFIGURE,"status.configure",&configure));
    predef.push_back(CA::xmlNodeSpec( caKEY_DEPLOY,"status.deploy",&deploy));
    predef.push_back(CA::xmlNodeSpec( caKEY_DOWNLOAD,"status.download",&download));
    predef.push_back(CA::xmlNodeSpec( caKEY_INSTALL,"status.install",&install));
    predef.push_back(CA::xmlNodeSpec( caKEY_PACKAGE,"status.package",&package));
    predef.push_back(CA::xmlNodeSpec( caKEY_PATCH,"status.patch",&patch));
    predef.push_back(CA::xmlNodeSpec( caKEY_POST_BUILD,"status.post_build",&post_build));
    predef.push_back(CA::xmlNodeSpec( caKEY_POST_CONFIGURE,"status.post_configure",&post_configure));
    predef.push_back(CA::xmlNodeSpec( caKEY_POST_DEPLOY,"status.post_deploy",&post_deploy));
    predef.push_back(CA::xmlNodeSpec( caKEY_POST_DOWNLOAD,"status.post_download",&post_download));
    predef.push_back(CA::xmlNodeSpec( caKEY_POST_INSTALL,"status.post_install",&post_install));
    predef.push_back(CA::xmlNodeSpec( caKEY_POST_PACKAGE,"status.post_package",&post_package));
    predef.push_back(CA::xmlNodeSpec( caKEY_POST_PATCH,"status.post_patch",&post_patch));
    predef.push_back(CA::xmlNodeSpec( caKEY_POST_SAVE_SOURCE,"status.post_save_source",&post_save_source));
    predef.push_back(CA::xmlNodeSpec( caKEY_PRE_BUILD,"status.pre_build",&pre_build));
    predef.push_back(CA::xmlNodeSpec( caKEY_PRE_CONFIGURE,"status.pre_configure",&pre_configure));
    predef.push_back(CA::xmlNodeSpec( caKEY_PRE_DEPLOY,"status.pre_deploy",&pre_deploy));
    predef.push_back(CA::xmlNodeSpec( caKEY_PRE_DOWNLOAD,"status.pre_download",&pre_download));
    predef.push_back(CA::xmlNodeSpec( caKEY_PRE_INSTALL,"status.pre_install",&pre_install));
    predef.push_back(CA::xmlNodeSpec( caKEY_PRE_PACKAGE,"status.pre_package",&pre_package));
    predef.push_back(CA::xmlNodeSpec( caKEY_PRE_PATCH,"status.pre_patch",&pre_patch));
    predef.push_back(CA::xmlNodeSpec( caKEY_PRE_SAVE_SOURCE,"status.pre_save_source",&pre_save_source));
    predef.push_back(CA::xmlNodeSpec( caKEY_SAVE_SOURCE,"status.save_source",&save_source));
}


bool CAXml_Status::loadFromXml(std::string filename){
bool res=false;
CA::IXmlNode *root=CA::IXmlNode::getNewNode();
if(root->load(filename)){
    loadFromXml(root);
    res=true;
   }
delete root;
return res;
}

