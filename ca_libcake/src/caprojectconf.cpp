
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
#include "caprojectconf.h"

const CA::_cbt *ICAXml_Project_Remote_Key::caKEY_FILE = "file";
const CA::_cbt *ICAXml_Project_Remote_Key::caKEY_URL = "url";
const CA::_cbt *ICAXml_Project_Remote_Key::mName="key";


CAXml_Project_Remote_Key::CAXml_Project_Remote_Key()
{
    predef.push_back(CA::xmlNodeSpec( caKEY_FILE,"project.remote.key.file",&file));
    predef.push_back(CA::xmlNodeSpec( caKEY_URL,"project.remote.key.url",&url));
}


const CA::_cbt *ICAXml_Project_Remote::caKEY_BRANCH = "branch";
const CA::_cbt *ICAXml_Project_Remote::caKEY_COMMIT = "commit";
const CA::_cbt *ICAXml_Project_Remote::caKEY_FILE = "file";
const CA::_cbt *ICAXml_Project_Remote::caKEY_KEY = "key";
const CA::_cbt *ICAXml_Project_Remote::caKEY_METHOD = "method";
const CA::_cbt *ICAXml_Project_Remote::caKEY_REVISION = "revision";
const CA::_cbt *ICAXml_Project_Remote::caKEY_URL = "url";
const CA::_cbt *ICAXml_Project_Remote::mName="remote";


CAXml_Project_Remote::CAXml_Project_Remote()
{
    predef.push_back(CA::xmlNodeSpec( caKEY_BRANCH,"project.remote.branch",&branch));
    predef.push_back(CA::xmlNodeSpec( caKEY_COMMIT,"project.remote.commit",&commit));
    predef.push_back(CA::xmlNodeSpec( caKEY_FILE,"project.remote.file",&file));
    predef.push_back(CA::xmlNodeSpec( caKEY_KEY,"project.remote.key",&key.node_internal_value,&key));
    predef.push_back(CA::xmlNodeSpec( caKEY_METHOD,"project.remote.method",&method));
    predef.push_back(CA::xmlNodeSpec( caKEY_REVISION,"project.remote.revision",&revision));
    predef.push_back(CA::xmlNodeSpec( caKEY_URL,"project.remote.url",&url));
}


const CA::_cbt *ICAXml_Project_Patch_Key::caKEY_FILE = "file";
const CA::_cbt *ICAXml_Project_Patch_Key::caKEY_URL = "url";
const CA::_cbt *ICAXml_Project_Patch_Key::mName="key";


CAXml_Project_Patch_Key::CAXml_Project_Patch_Key()
{
    predef.push_back(CA::xmlNodeSpec( caKEY_FILE,"project.patch.key.file",&file));
    predef.push_back(CA::xmlNodeSpec( caKEY_URL,"project.patch.key.url",&url));
}


const CA::_cbt *ICAXml_Project_Patch::caKEY_APPLY = "apply";
const CA::_cbt *ICAXml_Project_Patch::caKEY_BRANCH = "branch";
const CA::_cbt *ICAXml_Project_Patch::caKEY_COMMIT = "commit";
const CA::_cbt *ICAXml_Project_Patch::caKEY_DEST_DIR = "dest_dir";
const CA::_cbt *ICAXml_Project_Patch::caKEY_DIR = "dir";
const CA::_cbt *ICAXml_Project_Patch::caKEY_FILE = "file";
const CA::_cbt *ICAXml_Project_Patch::caKEY_KEY = "key";
const CA::_cbt *ICAXml_Project_Patch::caKEY_METHOD = "method";
const CA::_cbt *ICAXml_Project_Patch::caKEY_REVISION = "revision";
const CA::_cbt *ICAXml_Project_Patch::caKEY_URL = "url";
const CA::_cbt *ICAXml_Project_Patch::mName="patch";


CAXml_Project_Patch::CAXml_Project_Patch()
{
    predef.push_back(CA::xmlNodeSpec( caKEY_APPLY,"project.patch.apply",&apply));
    predef.push_back(CA::xmlNodeSpec( caKEY_BRANCH,"project.patch.branch",&branch));
    predef.push_back(CA::xmlNodeSpec( caKEY_COMMIT,"project.patch.commit",&commit));
    predef.push_back(CA::xmlNodeSpec( caKEY_DEST_DIR,"project.patch.dest_dir",&dest_dir));
    predef.push_back(CA::xmlNodeSpec( caKEY_DIR,"project.patch.dir",&dir));
    predef.push_back(CA::xmlNodeSpec( caKEY_FILE,"project.patch.file",&file));
    predef.push_back(CA::xmlNodeSpec( caKEY_KEY,"project.patch.key",&key.node_internal_value,&key));
    predef.push_back(CA::xmlNodeSpec( caKEY_METHOD,"project.patch.method",&method));
    predef.push_back(CA::xmlNodeSpec( caKEY_REVISION,"project.patch.revision",&revision));
    predef.push_back(CA::xmlNodeSpec( caKEY_URL,"project.patch.url",&url));
}


const CA::_cbt *ICAXml_Project_Build_Step_Path_Pre::caKEY_ADD = "add";
const CA::_cbt *ICAXml_Project_Build_Step_Path_Pre::caKEY_REMOVE = "remove";
const CA::_cbt *ICAXml_Project_Build_Step_Path_Pre::caKEY_SET = "set";
const CA::_cbt *ICAXml_Project_Build_Step_Path_Pre::mName="pre";


CAXml_Project_Build_Step_Path_Pre::CAXml_Project_Build_Step_Path_Pre()
{
    predef.push_back(CA::xmlNodeSpec( caKEY_ADD,"project.build.step.path.pre.add",&add));
    predef.push_back(CA::xmlNodeSpec( caKEY_REMOVE,"project.build.step.path.pre.remove",&remove));
    predef.push_back(CA::xmlNodeSpec( caKEY_SET,"project.build.step.path.pre.set",&set));
}


const CA::_cbt *ICAXml_Project_Build_Step_Path_Post::caKEY_ADD = "add";
const CA::_cbt *ICAXml_Project_Build_Step_Path_Post::caKEY_REMOVE = "remove";
const CA::_cbt *ICAXml_Project_Build_Step_Path_Post::caKEY_SET = "set";
const CA::_cbt *ICAXml_Project_Build_Step_Path_Post::mName="post";


CAXml_Project_Build_Step_Path_Post::CAXml_Project_Build_Step_Path_Post()
{
    predef.push_back(CA::xmlNodeSpec( caKEY_ADD,"project.build.step.path.post.add",&add));
    predef.push_back(CA::xmlNodeSpec( caKEY_REMOVE,"project.build.step.path.post.remove",&remove));
    predef.push_back(CA::xmlNodeSpec( caKEY_SET,"project.build.step.path.post.set",&set));
}


const CA::_cbt *ICAXml_Project_Build_Step_Path::caKEY_POST = "post";
const CA::_cbt *ICAXml_Project_Build_Step_Path::caKEY_PRE = "pre";
const CA::_cbt *ICAXml_Project_Build_Step_Path::mName="path";


CAXml_Project_Build_Step_Path::CAXml_Project_Build_Step_Path()
{
    predef.push_back(CA::xmlNodeSpec( caKEY_POST,"project.build.step.path.post",&post.node_internal_value,&post));
    predef.push_back(CA::xmlNodeSpec( caKEY_PRE,"project.build.step.path.pre",&pre.node_internal_value,&pre));
}


const CA::_cbt *ICAXml_Project_Build_Step_Pakage::caKEY_FILE = "file";
const CA::_cbt *ICAXml_Project_Build_Step_Pakage::caKEY_METHOD = "method";
const CA::_cbt *ICAXml_Project_Build_Step_Pakage::caKEY_SIGN = "sign";
const CA::_cbt *ICAXml_Project_Build_Step_Pakage::caKEY_URL = "url";
const CA::_cbt *ICAXml_Project_Build_Step_Pakage::mName="pakage";


CAXml_Project_Build_Step_Pakage::CAXml_Project_Build_Step_Pakage()
{
    predef.push_back(CA::xmlNodeSpec( caKEY_FILE,"project.build.step.pakage.file",&file));
    predef.push_back(CA::xmlNodeSpec( caKEY_METHOD,"project.build.step.pakage.method",&method));
    predef.push_back(CA::xmlNodeSpec( caKEY_SIGN,"project.build.step.pakage.sign",&sign));
    predef.push_back(CA::xmlNodeSpec( caKEY_URL,"project.build.step.pakage.url",&url));
}


const CA::_cbt *ICAXml_Project_Build_Step_Make_Rule_Pre::caKEY_CODE = "code";
const CA::_cbt *ICAXml_Project_Build_Step_Make_Rule_Pre::caKEY_SCRIPT = "script";
const CA::_cbt *ICAXml_Project_Build_Step_Make_Rule_Pre::caKEY_SOURCE = "source";
const CA::_cbt *ICAXml_Project_Build_Step_Make_Rule_Pre::mName="pre";


CAXml_Project_Build_Step_Make_Rule_Pre::CAXml_Project_Build_Step_Make_Rule_Pre()
{
    predef.push_back(CA::xmlNodeSpec( caKEY_CODE,"project.build.step.make.rule.pre.code",&code));
    predef.push_back(CA::xmlNodeSpec( caKEY_SCRIPT,"project.build.step.make.rule.pre.script",&script));
    predef.push_back(CA::xmlNodeSpec( caKEY_SOURCE,"project.build.step.make.rule.pre.source",&source));
}


const CA::_cbt *ICAXml_Project_Build_Step_Make_Rule_Post::caKEY_CODE = "code";
const CA::_cbt *ICAXml_Project_Build_Step_Make_Rule_Post::caKEY_SCRIPT = "script";
const CA::_cbt *ICAXml_Project_Build_Step_Make_Rule_Post::caKEY_SOURCE = "source";
const CA::_cbt *ICAXml_Project_Build_Step_Make_Rule_Post::mName="post";


CAXml_Project_Build_Step_Make_Rule_Post::CAXml_Project_Build_Step_Make_Rule_Post()
{
    predef.push_back(CA::xmlNodeSpec( caKEY_CODE,"project.build.step.make.rule.post.code",&code));
    predef.push_back(CA::xmlNodeSpec( caKEY_SCRIPT,"project.build.step.make.rule.post.script",&script));
    predef.push_back(CA::xmlNodeSpec( caKEY_SOURCE,"project.build.step.make.rule.post.source",&source));
}


const CA::_cbt *ICAXml_Project_Build_Step_Make_Rule::caKEY_NAME = "name";
const CA::_cbt *ICAXml_Project_Build_Step_Make_Rule::caKEY_POST = "post";
const CA::_cbt *ICAXml_Project_Build_Step_Make_Rule::caKEY_PRE = "pre";
const CA::_cbt *ICAXml_Project_Build_Step_Make_Rule::caKEY_THREAD = "thread";
const CA::_cbt *ICAXml_Project_Build_Step_Make_Rule::mName="rule";


CAXml_Project_Build_Step_Make_Rule::CAXml_Project_Build_Step_Make_Rule()
{
    predef.push_back(CA::xmlNodeSpec( caKEY_NAME,"project.build.step.make.rule.name",&name));
    predef.push_back(CA::xmlNodeSpec( caKEY_POST,"project.build.step.make.rule.post",&post.node_internal_value,&post));
    predef.push_back(CA::xmlNodeSpec( caKEY_PRE,"project.build.step.make.rule.pre",&pre.node_internal_value,&pre));
    predef.push_back(CA::xmlNodeSpec( caKEY_THREAD,"project.build.step.make.rule.thread",&thread));
}


const CA::_cbt *ICAXml_Project_Build_Step_Make::caKEY_PRIORITY = "priority";
const CA::_cbt *ICAXml_Project_Build_Step_Make::caKEY_RULE = "rule";
const CA::_cbt *ICAXml_Project_Build_Step_Make::caKEY_THREAD = "thread";
const CA::_cbt *ICAXml_Project_Build_Step_Make::mName="make";


CAXml_Project_Build_Step_Make::CAXml_Project_Build_Step_Make()
{
    predef.push_back(CA::xmlNodeSpec( caKEY_PRIORITY,"project.build.step.make.priority",&priority));
    predef.push_back(CA::xmlNodeSpec( caKEY_RULE,"project.build.step.make.rule",&rule,&rule_ref_clonable));
    predef.push_back(CA::xmlNodeSpec( caKEY_THREAD,"project.build.step.make.thread",&thread));
}


const CA::_cbt *ICAXml_Project_Build_Step_Configure_Pre::caKEY_CODE = "code";
const CA::_cbt *ICAXml_Project_Build_Step_Configure_Pre::caKEY_SCRIPT = "script";
const CA::_cbt *ICAXml_Project_Build_Step_Configure_Pre::caKEY_SOURCE = "source";
const CA::_cbt *ICAXml_Project_Build_Step_Configure_Pre::mName="pre";


CAXml_Project_Build_Step_Configure_Pre::CAXml_Project_Build_Step_Configure_Pre()
{
    predef.push_back(CA::xmlNodeSpec( caKEY_CODE,"project.build.step.configure.pre.code",&code));
    predef.push_back(CA::xmlNodeSpec( caKEY_SCRIPT,"project.build.step.configure.pre.script",&script));
    predef.push_back(CA::xmlNodeSpec( caKEY_SOURCE,"project.build.step.configure.pre.source",&source));
}


const CA::_cbt *ICAXml_Project_Build_Step_Configure_Post::caKEY_CODE = "code";
const CA::_cbt *ICAXml_Project_Build_Step_Configure_Post::caKEY_SCRIPT = "script";
const CA::_cbt *ICAXml_Project_Build_Step_Configure_Post::caKEY_SOURCE = "source";
const CA::_cbt *ICAXml_Project_Build_Step_Configure_Post::mName="post";


CAXml_Project_Build_Step_Configure_Post::CAXml_Project_Build_Step_Configure_Post()
{
    predef.push_back(CA::xmlNodeSpec( caKEY_CODE,"project.build.step.configure.post.code",&code));
    predef.push_back(CA::xmlNodeSpec( caKEY_SCRIPT,"project.build.step.configure.post.script",&script));
    predef.push_back(CA::xmlNodeSpec( caKEY_SOURCE,"project.build.step.configure.post.source",&source));
}


const CA::_cbt *ICAXml_Project_Build_Step_Configure::caKEY_PARAM = "param";
const CA::_cbt *ICAXml_Project_Build_Step_Configure::caKEY_POST = "post";
const CA::_cbt *ICAXml_Project_Build_Step_Configure::caKEY_PRE = "pre";
const CA::_cbt *ICAXml_Project_Build_Step_Configure::mName="configure";


CAXml_Project_Build_Step_Configure::CAXml_Project_Build_Step_Configure()
{
    predef.push_back(CA::xmlNodeSpec( caKEY_PARAM,"project.build.step.configure.param",&param));
    predef.push_back(CA::xmlNodeSpec( caKEY_POST,"project.build.step.configure.post",&post.node_internal_value,&post));
    predef.push_back(CA::xmlNodeSpec( caKEY_PRE,"project.build.step.configure.pre",&pre.node_internal_value,&pre));
}


const CA::_cbt *ICAXml_Project_Build_Step::caKEY_CONFIGURE = "configure";
const CA::_cbt *ICAXml_Project_Build_Step::caKEY_MAKE = "make";
const CA::_cbt *ICAXml_Project_Build_Step::caKEY_PAKAGE = "pakage";
const CA::_cbt *ICAXml_Project_Build_Step::caKEY_PATH = "path";
const CA::_cbt *ICAXml_Project_Build_Step::caKEY_SILENT = "silent";
const CA::_cbt *ICAXml_Project_Build_Step::caKEY_THREADS = "threads";
const CA::_cbt *ICAXml_Project_Build_Step::mName="step";


CAXml_Project_Build_Step::CAXml_Project_Build_Step()
{
    predef.push_back(CA::xmlNodeSpec( caKEY_CONFIGURE,"project.build.step.configure",&configure.node_internal_value,&configure));
    predef.push_back(CA::xmlNodeSpec( caKEY_MAKE,"project.build.step.make",&make,&make_ref_clonable));
    predef.push_back(CA::xmlNodeSpec( caKEY_PAKAGE,"project.build.step.pakage",&pakage.node_internal_value,&pakage));
    predef.push_back(CA::xmlNodeSpec( caKEY_PATH,"project.build.step.path",&path.node_internal_value,&path));
    predef.push_back(CA::xmlNodeSpec( caKEY_SILENT,"project.build.step.silent",&silent));
    predef.push_back(CA::xmlNodeSpec( caKEY_THREADS,"project.build.step.threads",&threads));
}


const CA::_cbt *ICAXml_Project_Build::caKEY_STEP = "step";
const CA::_cbt *ICAXml_Project_Build::mName="build";


CAXml_Project_Build::CAXml_Project_Build()
{
    predef.push_back(CA::xmlNodeSpec( caKEY_STEP,"project.build.step",&step,&step_ref_clonable_option));
}


const CA::_cbt *ICAXml_Project::caKEY_BUILD = "build";
const CA::_cbt *ICAXml_Project::caKEY_NAME = "name";
const CA::_cbt *ICAXml_Project::caKEY_PATCH = "patch";
const CA::_cbt *ICAXml_Project::caKEY_REMOTE = "remote";
const CA::_cbt *ICAXml_Project::mName="project";


CAXml_Project::CAXml_Project()
{
    predef.push_back(CA::xmlNodeSpec( caKEY_BUILD,"project.build",&build.node_internal_value,&build));
    predef.push_back(CA::xmlNodeSpec( caKEY_NAME,"project.name",&name));
    predef.push_back(CA::xmlNodeSpec( caKEY_PATCH,"project.patch",&patch,&patch_ref_clonable));
    predef.push_back(CA::xmlNodeSpec( caKEY_REMOTE,"project.remote",&remote,&remote_ref_clonable));
}


CAXml_Project::~CAXml_Project()
{
    CA::LCFXml::deleteChildsArray(&patch);
    CA::LCFXml::deleteChildsArray(&remote);
}


bool CAXml_Project::loadFromXml(std::string filename)
{
    bool res=false;
    CA::IXmlNode *root=CA::IXmlNode::getNewNode();
    if(root->load(filename))
    {
        loadFromXml(root);
        res=true;
    }
    delete root;
    return res;
}

