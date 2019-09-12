
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
#include "calayerconf.h"

const CA::_cbt *ICAXml_Layer_Maxtask::caKEY_BUILD = "build";
const CA::_cbt *ICAXml_Layer_Maxtask::caKEY_DEPLOY = "deploy";
const CA::_cbt *ICAXml_Layer_Maxtask::caKEY_PACKAGE = "package";
const CA::_cbt *ICAXml_Layer_Maxtask::caKEY_SOURCE = "source";
const CA::_cbt *ICAXml_Layer_Maxtask::mName="maxtask";


CAXml_Layer_Maxtask::CAXml_Layer_Maxtask(){
    predef.push_back(CA::xmlNodeSpec( caKEY_BUILD,"layer.maxtask.build",&build));
    predef.push_back(CA::xmlNodeSpec( caKEY_DEPLOY,"layer.maxtask.deploy",&deploy));
    predef.push_back(CA::xmlNodeSpec( caKEY_PACKAGE,"layer.maxtask.package",&package));
    predef.push_back(CA::xmlNodeSpec( caKEY_SOURCE,"layer.maxtask.source",&source));
}


const CA::_cbt *ICAXml_Layer::caKEY_INCLUDE = "include";
const CA::_cbt *ICAXml_Layer::caKEY_INFO = "info";
const CA::_cbt *ICAXml_Layer::caKEY_MAXTASK = "maxtask";
const CA::_cbt *ICAXml_Layer::caKEY_NAME = "name";
const CA::_cbt *ICAXml_Layer::mName="layer";


CAXml_Layer::CAXml_Layer(){
    predef.push_back(CA::xmlNodeSpec( caKEY_INCLUDE,"layer.include",&include));
    predef.push_back(CA::xmlNodeSpec( caKEY_INFO,"layer.info",&info));
    predef.push_back(CA::xmlNodeSpec( caKEY_MAXTASK,"layer.maxtask",&maxtask.node_internal_value,&maxtask));
    predef.push_back(CA::xmlNodeSpec( caKEY_NAME,"layer.name",&name));
}


bool CAXml_Layer::loadFromXml(std::string filename){
bool res=false;
CA::IXmlNode *root=CA::IXmlNode::getNewNode();
if(root->load(filename)){
    loadFromXml(root);
    res=true;
   }
delete root;
return res;
}

