#ifndef CAPROJECTCONF_HEADER
#define CAPROJECTCONF_HEADER

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

/// declare interface ICAXml_Project_Remote_Key for node <key>
class ICAXml_Project_Remote_Key
{
protected:
    static const CA::_cbt *  caKEY_FILE;
    static const CA::_cbt *  caKEY_URL;
    static const CA::_cbt *   mName;

public:
    virtual ~ICAXml_Project_Remote_Key()=default;
};


/// declare interface ICAXml_Project_Remote for node <remote>
class ICAXml_Project_Remote
{
protected:
    static const CA::_cbt *  caKEY_BRANCH;
    static const CA::_cbt *  caKEY_COMMIT;
    static const CA::_cbt *  caKEY_FILE;
    static const CA::_cbt *  caKEY_KEY;
    static const CA::_cbt *  caKEY_METHOD;
    static const CA::_cbt *  caKEY_REVISION;
    static const CA::_cbt *  caKEY_URL;
    static const CA::_cbt *   mName;

public:
    virtual ~ICAXml_Project_Remote()=default;
};


/// declare interface ICAXml_Project_Patch_Key for node <key>
class ICAXml_Project_Patch_Key
{
protected:
    static const CA::_cbt *  caKEY_FILE;
    static const CA::_cbt *  caKEY_URL;
    static const CA::_cbt *   mName;

public:
    virtual ~ICAXml_Project_Patch_Key()=default;
};


/// declare interface ICAXml_Project_Patch for node <patch>
class ICAXml_Project_Patch
{
protected:
    static const CA::_cbt *  caKEY_APPLY;
    static const CA::_cbt *  caKEY_BRANCH;
    static const CA::_cbt *  caKEY_COMMIT;
    static const CA::_cbt *  caKEY_DEST_DIR;
    static const CA::_cbt *  caKEY_DIR;
    static const CA::_cbt *  caKEY_FILE;
    static const CA::_cbt *  caKEY_KEY;
    static const CA::_cbt *  caKEY_METHOD;
    static const CA::_cbt *  caKEY_REVISION;
    static const CA::_cbt *  caKEY_URL;
    static const CA::_cbt *   mName;

public:
    virtual ~ICAXml_Project_Patch()=default;
};


/// declare interface ICAXml_Project_Build_Step_Path_Pre for node <pre>
class ICAXml_Project_Build_Step_Path_Pre
{
protected:
    static const CA::_cbt *  caKEY_ADD;
    static const CA::_cbt *  caKEY_REMOVE;
    static const CA::_cbt *  caKEY_SET;
    static const CA::_cbt *   mName;

public:
    virtual ~ICAXml_Project_Build_Step_Path_Pre()=default;
};


/// declare interface ICAXml_Project_Build_Step_Path_Post for node <post>
class ICAXml_Project_Build_Step_Path_Post
{
protected:
    static const CA::_cbt *  caKEY_ADD;
    static const CA::_cbt *  caKEY_REMOVE;
    static const CA::_cbt *  caKEY_SET;
    static const CA::_cbt *   mName;

public:
    virtual ~ICAXml_Project_Build_Step_Path_Post()=default;
};


/// declare interface ICAXml_Project_Build_Step_Path for node <path>
class ICAXml_Project_Build_Step_Path
{
protected:
    static const CA::_cbt *  caKEY_POST;
    static const CA::_cbt *  caKEY_PRE;
    static const CA::_cbt *   mName;

public:
    virtual ~ICAXml_Project_Build_Step_Path()=default;
};


/// declare interface ICAXml_Project_Build_Step_Pakage for node <pakage>
class ICAXml_Project_Build_Step_Pakage
{
protected:
    static const CA::_cbt *  caKEY_FILE;
    static const CA::_cbt *  caKEY_METHOD;
    static const CA::_cbt *  caKEY_SIGN;
    static const CA::_cbt *  caKEY_URL;
    static const CA::_cbt *   mName;

public:
    virtual ~ICAXml_Project_Build_Step_Pakage()=default;
};


/// declare interface ICAXml_Project_Build_Step_Make_Rule_Pre for node <pre>
class ICAXml_Project_Build_Step_Make_Rule_Pre
{
protected:
    static const CA::_cbt *  caKEY_CODE;
    static const CA::_cbt *  caKEY_SCRIPT;
    static const CA::_cbt *  caKEY_SOURCE;
    static const CA::_cbt *   mName;

public:
    virtual ~ICAXml_Project_Build_Step_Make_Rule_Pre()=default;
};


/// declare interface ICAXml_Project_Build_Step_Make_Rule_Post for node <post>
class ICAXml_Project_Build_Step_Make_Rule_Post
{
protected:
    static const CA::_cbt *  caKEY_CODE;
    static const CA::_cbt *  caKEY_SCRIPT;
    static const CA::_cbt *  caKEY_SOURCE;
    static const CA::_cbt *   mName;

public:
    virtual ~ICAXml_Project_Build_Step_Make_Rule_Post()=default;
};


/// declare interface ICAXml_Project_Build_Step_Make_Rule for node <rule>
class ICAXml_Project_Build_Step_Make_Rule
{
protected:
    static const CA::_cbt *  caKEY_NAME;
    static const CA::_cbt *  caKEY_POST;
    static const CA::_cbt *  caKEY_PRE;
    static const CA::_cbt *  caKEY_THREAD;
    static const CA::_cbt *   mName;

public:
    virtual ~ICAXml_Project_Build_Step_Make_Rule()=default;
};


/// declare interface ICAXml_Project_Build_Step_Make for node <make>
class ICAXml_Project_Build_Step_Make
{
protected:
    static const CA::_cbt *  caKEY_PRIORITY;
    static const CA::_cbt *  caKEY_RULE;
    static const CA::_cbt *  caKEY_THREAD;
    static const CA::_cbt *   mName;

public:
    virtual ~ICAXml_Project_Build_Step_Make()=default;
};


/// declare interface ICAXml_Project_Build_Step_Configure_Pre for node <pre>
class ICAXml_Project_Build_Step_Configure_Pre
{
protected:
    static const CA::_cbt *  caKEY_CODE;
    static const CA::_cbt *  caKEY_SCRIPT;
    static const CA::_cbt *  caKEY_SOURCE;
    static const CA::_cbt *   mName;

public:
    virtual ~ICAXml_Project_Build_Step_Configure_Pre()=default;
};


/// declare interface ICAXml_Project_Build_Step_Configure_Post for node <post>
class ICAXml_Project_Build_Step_Configure_Post
{
protected:
    static const CA::_cbt *  caKEY_CODE;
    static const CA::_cbt *  caKEY_SCRIPT;
    static const CA::_cbt *  caKEY_SOURCE;
    static const CA::_cbt *   mName;

public:
    virtual ~ICAXml_Project_Build_Step_Configure_Post()=default;
};


/// declare interface ICAXml_Project_Build_Step_Configure for node <configure>
class ICAXml_Project_Build_Step_Configure
{
protected:
    static const CA::_cbt *  caKEY_PARAM;
    static const CA::_cbt *  caKEY_POST;
    static const CA::_cbt *  caKEY_PRE;
    static const CA::_cbt *   mName;

public:
    virtual ~ICAXml_Project_Build_Step_Configure()=default;
};


/// declare interface ICAXml_Project_Build_Step for node <step>
class ICAXml_Project_Build_Step
{
protected:
    static const CA::_cbt *  caKEY_CONFIGURE;
    static const CA::_cbt *  caKEY_MAKE;
    static const CA::_cbt *  caKEY_PAKAGE;
    static const CA::_cbt *  caKEY_PATH;
    static const CA::_cbt *  caKEY_SILENT;
    static const CA::_cbt *  caKEY_THREADS;
    static const CA::_cbt *   mName;

public:
    virtual ~ICAXml_Project_Build_Step()=default;
};


/// declare interface ICAXml_Project_Build for node <build>
class ICAXml_Project_Build
{
protected:
    static const CA::_cbt *  caKEY_STEP;
    static const CA::_cbt *   mName;

public:
    virtual ~ICAXml_Project_Build()=default;
};


/// declare interface ICAXml_Project for node <project>
class ICAXml_Project
{
protected:
    static const CA::_cbt *  caKEY_BUILD;
    static const CA::_cbt *  caKEY_NAME;
    static const CA::_cbt *  caKEY_PATCH;
    static const CA::_cbt *  caKEY_REMOTE;
    static const CA::_cbt *   mName;

public:
    virtual ~ICAXml_Project()=default;
    virtual bool loadFromXml(std::string filename)=0;
    virtual void toString(std::iostream &ss)=0;
};


/// implement interface ICAXml_Project_Remote_Key : as CAXml_Project_Remote_Key
class CAXml_Project_Remote_Key
    : public ICAXml_Project_Remote_Key
    , public CA::IKeyValue
{
protected:
    CA::keyList predef;

public:
/// ctor
    CAXml_Project_Remote_Key();
/// value of this node :
    std::string node_internal_value;
/// value of node : project.remote.key.file
    std::string file;
/// value of node : project.remote.key.url
    std::string url;
public:
/// getters
/// return this node name
    inline const CA::_cbt * getICAXml_Name_Value() final
    {
        return mName;
    }

/// return list of predefined childs node name
    inline CA::keyList *  getICAXml_Predef_List() final
    {
        return &predef;
    }

/// load from IXmlNode
    inline void loadFromXml(CA::IXmlNode *node) final
    {
        CA::LCFXml::loadFromXml(node,this);
    }
/// human readable to map as pair key value
    void toMap(std::map<std::string,std::string> & outmap,bool ucase=true)
    {
        CA::LCFXml::toMap(outmap,this,ucase);
    }
};


/// implement interface ICAXml_Project_Remote : as CAXml_Project_Remote
class CAXml_Project_Remote
    : public ICAXml_Project_Remote
    , public CA::IClonable
{
protected:
    CA::keyList predef;

public:
/// ctor
    CAXml_Project_Remote();
/// value of this node :
    std::string node_internal_value;
/// value of node : project.remote.branch
    std::string branch;
/// value of node : project.remote.commit
    std::string commit;
/// value of node : project.remote.file
    std::string file;
/// object for node : project.remote.key
    CAXml_Project_Remote_Key key;
/// value of node : project.remote.method
    std::string method;
/// value of node : project.remote.revision
    std::string revision;
/// value of node : project.remote.url
    std::string url;
public:
/// getters
/// return this node name
    inline const CA::_cbt * getICAXml_Name_Value() final
    {
        return mName;
    }

/// return list of predefined childs node name
    inline CA::keyList *  getICAXml_Predef_List() final
    {
        return &predef;
    }

/// load from IXmlNode
    inline void loadFromXml(CA::IXmlNode *node) final
    {
        CA::LCFXml::loadFromXml(node,this);
    }
/// human readable to map as pair key value
    void toMap(std::map<std::string,std::string> & outmap,bool ucase=true)
    {
        CA::LCFXml::toMap(outmap,this,ucase);
    }
/// return a clone of Unknow Obj
    inline CA::IClonable *clone() final
    {
        return new CAXml_Project_Remote();
    }
/// return a value of complex child node
    inline const CA::_cbt * getInternalValue() final
    {
        return node_internal_value.c_str();
    }
/// Set the  value of complex child node
    inline void setInternalValue(std::string &str) final
    {
        node_internal_value=str;
    }
};


/// implement interface ICAXml_Project_Patch_Key : as CAXml_Project_Patch_Key
class CAXml_Project_Patch_Key
    : public ICAXml_Project_Patch_Key
    , public CA::IKeyValue
{
protected:
    CA::keyList predef;

public:
/// ctor
    CAXml_Project_Patch_Key();
/// value of this node :
    std::string node_internal_value;
/// value of node : project.patch.key.file
    std::string file;
/// value of node : project.patch.key.url
    std::string url;
public:
/// getters
/// return this node name
    inline const CA::_cbt * getICAXml_Name_Value() final
    {
        return mName;
    }

/// return list of predefined childs node name
    inline CA::keyList *  getICAXml_Predef_List() final
    {
        return &predef;
    }

/// load from IXmlNode
    inline void loadFromXml(CA::IXmlNode *node) final
    {
        CA::LCFXml::loadFromXml(node,this);
    }
/// human readable to map as pair key value
    void toMap(std::map<std::string,std::string> & outmap,bool ucase=true)
    {
        CA::LCFXml::toMap(outmap,this,ucase);
    }
};


/// implement interface ICAXml_Project_Patch : as CAXml_Project_Patch
class CAXml_Project_Patch
    : public ICAXml_Project_Patch
    , public CA::IClonable
{
protected:
    CA::keyList predef;

public:
/// ctor
    CAXml_Project_Patch();
/// value of this node :
    std::string node_internal_value;
/// value of nodes[] : project.patch.apply
    std::vector<std::string> apply;
/// value of node : project.patch.branch
    std::string branch;
/// value of node : project.patch.commit
    std::string commit;
/// value of node : project.patch.dest_dir
    std::string dest_dir;
/// value of node : project.patch.dir
    std::string dir;
/// value of node : project.patch.file
    std::string file;
/// object for node : project.patch.key
    CAXml_Project_Patch_Key key;
/// value of node : project.patch.method
    std::string method;
/// value of node : project.patch.revision
    std::string revision;
/// value of node : project.patch.url
    std::string url;
public:
/// getters
/// return this node name
    inline const CA::_cbt * getICAXml_Name_Value() final
    {
        return mName;
    }

/// return list of predefined childs node name
    inline CA::keyList *  getICAXml_Predef_List() final
    {
        return &predef;
    }

/// load from IXmlNode
    inline void loadFromXml(CA::IXmlNode *node) final
    {
        CA::LCFXml::loadFromXml(node,this);
    }
/// human readable to map as pair key value
    void toMap(std::map<std::string,std::string> & outmap,bool ucase=true)
    {
        CA::LCFXml::toMap(outmap,this,ucase);
    }
/// return a clone of Unknow Obj
    inline CA::IClonable *clone() final
    {
        return new CAXml_Project_Patch();
    }
/// return a value of complex child node
    inline const CA::_cbt * getInternalValue() final
    {
        return node_internal_value.c_str();
    }
/// Set the  value of complex child node
    inline void setInternalValue(std::string &str) final
    {
        node_internal_value=str;
    }
};


/// implement interface ICAXml_Project_Build_Step_Path_Pre : as CAXml_Project_Build_Step_Path_Pre
class CAXml_Project_Build_Step_Path_Pre
    : public ICAXml_Project_Build_Step_Path_Pre
    , public CA::IKeyValue
{
protected:
    CA::keyList predef;

public:
/// ctor
    CAXml_Project_Build_Step_Path_Pre();
/// value of this node :
    std::string node_internal_value;
/// value of nodes[] : project.build.step.path.pre.add
    std::vector<std::string> add;
/// value of nodes[] : project.build.step.path.pre.remove
    std::vector<std::string> remove;
/// value of node : project.build.step.path.pre.set
    std::string set;
public:
/// getters
/// return this node name
    inline const CA::_cbt * getICAXml_Name_Value() final
    {
        return mName;
    }

/// return list of predefined childs node name
    inline CA::keyList *  getICAXml_Predef_List() final
    {
        return &predef;
    }

/// load from IXmlNode
    inline void loadFromXml(CA::IXmlNode *node) final
    {
        CA::LCFXml::loadFromXml(node,this);
    }
/// human readable to map as pair key value
    void toMap(std::map<std::string,std::string> & outmap,bool ucase=true)
    {
        CA::LCFXml::toMap(outmap,this,ucase);
    }
};


/// implement interface ICAXml_Project_Build_Step_Path_Post : as CAXml_Project_Build_Step_Path_Post
class CAXml_Project_Build_Step_Path_Post
    : public ICAXml_Project_Build_Step_Path_Post
    , public CA::IKeyValue
{
protected:
    CA::keyList predef;

public:
/// ctor
    CAXml_Project_Build_Step_Path_Post();
/// value of this node :
    std::string node_internal_value;
/// value of nodes[] : project.build.step.path.post.add
    std::vector<std::string> add;
/// value of nodes[] : project.build.step.path.post.remove
    std::vector<std::string> remove;
/// value of node : project.build.step.path.post.set
    std::string set;
public:
/// getters
/// return this node name
    inline const CA::_cbt * getICAXml_Name_Value() final
    {
        return mName;
    }

/// return list of predefined childs node name
    inline CA::keyList *  getICAXml_Predef_List() final
    {
        return &predef;
    }

/// load from IXmlNode
    inline void loadFromXml(CA::IXmlNode *node) final
    {
        CA::LCFXml::loadFromXml(node,this);
    }
/// human readable to map as pair key value
    void toMap(std::map<std::string,std::string> & outmap,bool ucase=true)
    {
        CA::LCFXml::toMap(outmap,this,ucase);
    }
};


/// implement interface ICAXml_Project_Build_Step_Path : as CAXml_Project_Build_Step_Path
class CAXml_Project_Build_Step_Path
    : public ICAXml_Project_Build_Step_Path
    , public CA::IKeyValue
{
protected:
    CA::keyList predef;

public:
/// ctor
    CAXml_Project_Build_Step_Path();
/// value of this node :
    std::string node_internal_value;
/// object for node : project.build.step.path.post
    CAXml_Project_Build_Step_Path_Post post;
/// object for node : project.build.step.path.pre
    CAXml_Project_Build_Step_Path_Pre pre;
public:
/// getters
/// return this node name
    inline const CA::_cbt * getICAXml_Name_Value() final
    {
        return mName;
    }

/// return list of predefined childs node name
    inline CA::keyList *  getICAXml_Predef_List() final
    {
        return &predef;
    }

/// load from IXmlNode
    inline void loadFromXml(CA::IXmlNode *node) final
    {
        CA::LCFXml::loadFromXml(node,this);
    }
/// human readable to map as pair key value
    void toMap(std::map<std::string,std::string> & outmap,bool ucase=true)
    {
        CA::LCFXml::toMap(outmap,this,ucase);
    }
};


/// implement interface ICAXml_Project_Build_Step_Pakage : as CAXml_Project_Build_Step_Pakage
class CAXml_Project_Build_Step_Pakage
    : public ICAXml_Project_Build_Step_Pakage
    , public CA::IKeyValue
{
protected:
    CA::keyList predef;

public:
/// ctor
    CAXml_Project_Build_Step_Pakage();
/// value of this node :
    std::string node_internal_value;
/// value of node : project.build.step.pakage.file
    std::string file;
/// value of node : project.build.step.pakage.method
    std::string method;
/// value of node : project.build.step.pakage.sign
    std::string sign;
/// value of node : project.build.step.pakage.url
    std::string url;
public:
/// getters
/// return this node name
    inline const CA::_cbt * getICAXml_Name_Value() final
    {
        return mName;
    }

/// return list of predefined childs node name
    inline CA::keyList *  getICAXml_Predef_List() final
    {
        return &predef;
    }

/// load from IXmlNode
    inline void loadFromXml(CA::IXmlNode *node) final
    {
        CA::LCFXml::loadFromXml(node,this);
    }
/// human readable to map as pair key value
    void toMap(std::map<std::string,std::string> & outmap,bool ucase=true)
    {
        CA::LCFXml::toMap(outmap,this,ucase);
    }
};


/// implement interface ICAXml_Project_Build_Step_Make_Rule_Pre : as CAXml_Project_Build_Step_Make_Rule_Pre
class CAXml_Project_Build_Step_Make_Rule_Pre
    : public ICAXml_Project_Build_Step_Make_Rule_Pre
    , public CA::IKeyValue
{
protected:
    CA::keyList predef;

public:
/// ctor
    CAXml_Project_Build_Step_Make_Rule_Pre();
/// value of this node :
    std::string node_internal_value;
/// value of nodes[] : project.build.step.make.rule.pre.code
    std::vector<std::string> code;
/// value of nodes[] : project.build.step.make.rule.pre.script
    std::vector<std::string> script;
/// value of nodes[] : project.build.step.make.rule.pre.source
    std::vector<std::string> source;
public:
/// getters
/// return this node name
    inline const CA::_cbt * getICAXml_Name_Value() final
    {
        return mName;
    }

/// return list of predefined childs node name
    inline CA::keyList *  getICAXml_Predef_List() final
    {
        return &predef;
    }

/// load from IXmlNode
    inline void loadFromXml(CA::IXmlNode *node) final
    {
        CA::LCFXml::loadFromXml(node,this);
    }
/// human readable to map as pair key value
    void toMap(std::map<std::string,std::string> & outmap,bool ucase=true)
    {
        CA::LCFXml::toMap(outmap,this,ucase);
    }
};


/// implement interface ICAXml_Project_Build_Step_Make_Rule_Post : as CAXml_Project_Build_Step_Make_Rule_Post
class CAXml_Project_Build_Step_Make_Rule_Post
    : public ICAXml_Project_Build_Step_Make_Rule_Post
    , public CA::IKeyValue
{
protected:
    CA::keyList predef;

public:
/// ctor
    CAXml_Project_Build_Step_Make_Rule_Post();
/// value of this node :
    std::string node_internal_value;
/// value of nodes[] : project.build.step.make.rule.post.code
    std::vector<std::string> code;
/// value of nodes[] : project.build.step.make.rule.post.script
    std::vector<std::string> script;
/// value of nodes[] : project.build.step.make.rule.post.source
    std::vector<std::string> source;
public:
/// getters
/// return this node name
    inline const CA::_cbt * getICAXml_Name_Value() final
    {
        return mName;
    }

/// return list of predefined childs node name
    inline CA::keyList *  getICAXml_Predef_List() final
    {
        return &predef;
    }

/// load from IXmlNode
    inline void loadFromXml(CA::IXmlNode *node) final
    {
        CA::LCFXml::loadFromXml(node,this);
    }
/// human readable to map as pair key value
    void toMap(std::map<std::string,std::string> & outmap,bool ucase=true)
    {
        CA::LCFXml::toMap(outmap,this,ucase);
    }
};


/// implement interface ICAXml_Project_Build_Step_Make_Rule : as CAXml_Project_Build_Step_Make_Rule
class CAXml_Project_Build_Step_Make_Rule
    : public ICAXml_Project_Build_Step_Make_Rule
    , public CA::IClonable
{
protected:
    CA::keyList predef;

public:
/// ctor
    CAXml_Project_Build_Step_Make_Rule();
/// value of this node :
    std::string node_internal_value;
/// value of node : project.build.step.make.rule.name
    std::string name;
/// object for node : project.build.step.make.rule.post
    CAXml_Project_Build_Step_Make_Rule_Post post;
/// object for node : project.build.step.make.rule.pre
    CAXml_Project_Build_Step_Make_Rule_Pre pre;
/// value of node : project.build.step.make.rule.thread
    std::string thread;
public:
/// getters
/// return this node name
    inline const CA::_cbt * getICAXml_Name_Value() final
    {
        return mName;
    }

/// return list of predefined childs node name
    inline CA::keyList *  getICAXml_Predef_List() final
    {
        return &predef;
    }

/// load from IXmlNode
    inline void loadFromXml(CA::IXmlNode *node) final
    {
        CA::LCFXml::loadFromXml(node,this);
    }
/// human readable to map as pair key value
    void toMap(std::map<std::string,std::string> & outmap,bool ucase=true)
    {
        CA::LCFXml::toMap(outmap,this,ucase);
    }
/// return a clone of Unknow Obj
    inline CA::IClonable *clone() final
    {
        return new CAXml_Project_Build_Step_Make_Rule();
    }
/// return a value of complex child node
    inline const CA::_cbt * getInternalValue() final
    {
        return node_internal_value.c_str();
    }
/// Set the  value of complex child node
    inline void setInternalValue(std::string &str) final
    {
        node_internal_value=str;
    }
};


/// implement interface ICAXml_Project_Build_Step_Make : as CAXml_Project_Build_Step_Make
class CAXml_Project_Build_Step_Make
    : public ICAXml_Project_Build_Step_Make
    , public CA::IClonable
{
protected:
    CA::keyList predef;

public:
/// ctor
    CAXml_Project_Build_Step_Make();
/// value of this node :
    std::string node_internal_value;
/// value of node : project.build.step.make.priority
    std::string priority;
/// object for nodes[] : project.build.step.make.rule
    std::vector<CA::IClonable *> rule;
    CAXml_Project_Build_Step_Make_Rule  rule_ref_clonable;
/// value of node : project.build.step.make.thread
    std::string thread;
public:
/// getters
/// return this node name
    inline const CA::_cbt * getICAXml_Name_Value() final
    {
        return mName;
    }

/// return list of predefined childs node name
    inline CA::keyList *  getICAXml_Predef_List() final
    {
        return &predef;
    }

/// load from IXmlNode
    inline void loadFromXml(CA::IXmlNode *node) final
    {
        CA::LCFXml::loadFromXml(node,this);
    }
/// human readable to map as pair key value
    void toMap(std::map<std::string,std::string> & outmap,bool ucase=true)
    {
        CA::LCFXml::toMap(outmap,this,ucase);
    }
/// return a clone of Unknow Obj
    inline CA::IClonable *clone() final
    {
        return new CAXml_Project_Build_Step_Make();
    }
/// return a value of complex child node
    inline const CA::_cbt * getInternalValue() final
    {
        return node_internal_value.c_str();
    }
/// Set the  value of complex child node
    inline void setInternalValue(std::string &str) final
    {
        node_internal_value=str;
    }
};


/// implement interface ICAXml_Project_Build_Step_Configure_Pre : as CAXml_Project_Build_Step_Configure_Pre
class CAXml_Project_Build_Step_Configure_Pre
    : public ICAXml_Project_Build_Step_Configure_Pre
    , public CA::IKeyValue
{
protected:
    CA::keyList predef;

public:
/// ctor
    CAXml_Project_Build_Step_Configure_Pre();
/// value of this node :
    std::string node_internal_value;
/// value of nodes[] : project.build.step.configure.pre.code
    std::vector<std::string> code;
/// value of nodes[] : project.build.step.configure.pre.script
    std::vector<std::string> script;
/// value of nodes[] : project.build.step.configure.pre.source
    std::vector<std::string> source;
public:
/// getters
/// return this node name
    inline const CA::_cbt * getICAXml_Name_Value() final
    {
        return mName;
    }

/// return list of predefined childs node name
    inline CA::keyList *  getICAXml_Predef_List() final
    {
        return &predef;
    }

/// load from IXmlNode
    inline void loadFromXml(CA::IXmlNode *node) final
    {
        CA::LCFXml::loadFromXml(node,this);
    }
/// human readable to map as pair key value
    void toMap(std::map<std::string,std::string> & outmap,bool ucase=true)
    {
        CA::LCFXml::toMap(outmap,this,ucase);
    }
};


/// implement interface ICAXml_Project_Build_Step_Configure_Post : as CAXml_Project_Build_Step_Configure_Post
class CAXml_Project_Build_Step_Configure_Post
    : public ICAXml_Project_Build_Step_Configure_Post
    , public CA::IKeyValue
{
protected:
    CA::keyList predef;

public:
/// ctor
    CAXml_Project_Build_Step_Configure_Post();
/// value of this node :
    std::string node_internal_value;
/// value of nodes[] : project.build.step.configure.post.code
    std::vector<std::string> code;
/// value of nodes[] : project.build.step.configure.post.script
    std::vector<std::string> script;
/// value of nodes[] : project.build.step.configure.post.source
    std::vector<std::string> source;
public:
/// getters
/// return this node name
    inline const CA::_cbt * getICAXml_Name_Value() final
    {
        return mName;
    }

/// return list of predefined childs node name
    inline CA::keyList *  getICAXml_Predef_List() final
    {
        return &predef;
    }

/// load from IXmlNode
    inline void loadFromXml(CA::IXmlNode *node) final
    {
        CA::LCFXml::loadFromXml(node,this);
    }
/// human readable to map as pair key value
    void toMap(std::map<std::string,std::string> & outmap,bool ucase=true)
    {
        CA::LCFXml::toMap(outmap,this,ucase);
    }
};


/// implement interface ICAXml_Project_Build_Step_Configure : as CAXml_Project_Build_Step_Configure
class CAXml_Project_Build_Step_Configure
    : public ICAXml_Project_Build_Step_Configure
    , public CA::IKeyValue
{
protected:
    CA::keyList predef;

public:
/// ctor
    CAXml_Project_Build_Step_Configure();
/// value of this node :
    std::string node_internal_value;
/// value of nodes[] : project.build.step.configure.param
    std::vector<std::string> param;
/// object for node : project.build.step.configure.post
    CAXml_Project_Build_Step_Configure_Post post;
/// object for node : project.build.step.configure.pre
    CAXml_Project_Build_Step_Configure_Pre pre;
public:
/// getters
/// return this node name
    inline const CA::_cbt * getICAXml_Name_Value() final
    {
        return mName;
    }

/// return list of predefined childs node name
    inline CA::keyList *  getICAXml_Predef_List() final
    {
        return &predef;
    }

/// load from IXmlNode
    inline void loadFromXml(CA::IXmlNode *node) final
    {
        CA::LCFXml::loadFromXml(node,this);
    }
/// human readable to map as pair key value
    void toMap(std::map<std::string,std::string> & outmap,bool ucase=true)
    {
        CA::LCFXml::toMap(outmap,this,ucase);
    }
};


/// implement interface ICAXml_Project_Build_Step : as CAXml_Project_Build_Step
class CAXml_Project_Build_Step
    : public ICAXml_Project_Build_Step
    , public CA::IClonableOption
{
protected:
    CA::keyList predef;

public:
/// ctor
    CAXml_Project_Build_Step();
/// value of this node :
    std::string node_internal_value;
/// options of this node :
    CA::optionsList node_internal_options;
/// object for node : project.build.step.configure
    CAXml_Project_Build_Step_Configure configure;
/// object for nodes[] : project.build.step.make
    std::vector<CA::IClonable *> make;
    CAXml_Project_Build_Step_Make  make_ref_clonable;
/// object for node : project.build.step.pakage
    CAXml_Project_Build_Step_Pakage pakage;
/// object for node : project.build.step.path
    CAXml_Project_Build_Step_Path path;
/// value of node : project.build.step.silent
    std::string silent;
/// value of node : project.build.step.threads
    std::string threads;
public:
/// getters
/// return this node name
    inline const CA::_cbt * getICAXml_Name_Value() final
    {
        return mName;
    }

/// return list of predefined childs node name
    inline CA::keyList *  getICAXml_Predef_List() final
    {
        return &predef;
    }

/// load from IXmlNode
    inline void loadFromXml(CA::IXmlNode *node) final
    {
        CA::LCFXml::loadFromXml(node,this);
    }
/// human readable to map as pair key value
    void toMap(std::map<std::string,std::string> & outmap,bool ucase=true)
    {
        CA::LCFXml::toMap(outmap,this,ucase);
    }
/// return a clone of Unknow Obj
    inline CA::IClonable *clone() final
    {
        return new CAXml_Project_Build_Step();
    }
/// return a value of complex child node
    inline const CA::_cbt * getInternalValue() final
    {
        return node_internal_value.c_str();
    }
/// Set the  value of complex child node
    inline void setInternalValue(std::string &str) final
    {
        node_internal_value=str;
    }
/// return the  option list  of complex child node
    inline CA::optionsList & getOptionsList() final
    {
        return node_internal_options;
    }
/// set the  option list  of complex child node
    inline void setOptionList(CA::optionsList & optl)  final
    {
        if(!optl.empty())
        {
            auto it=optl.begin();
            auto _end=optl.end();
            while(it!=_end)
            {
                CA::optionPair p(it->first,it->second);
                node_internal_options.insert(p);
                it++;
            }
        }
    }
};


/// implement interface ICAXml_Project_Build : as CAXml_Project_Build
class CAXml_Project_Build
    : public ICAXml_Project_Build
    , public CA::IKeyValue
{
protected:
    CA::keyList predef;

public:
/// ctor
    CAXml_Project_Build();
/// value of this node :
    std::string node_internal_value;
/// object for nodes[] : project.build.step
    std::vector<CA::IClonableOption *> step;
    CAXml_Project_Build_Step  step_ref_clonable_option;
public:
/// getters
/// return this node name
    inline const CA::_cbt * getICAXml_Name_Value() final
    {
        return mName;
    }

/// return list of predefined childs node name
    inline CA::keyList *  getICAXml_Predef_List() final
    {
        return &predef;
    }

/// load from IXmlNode
    inline void loadFromXml(CA::IXmlNode *node) final
    {
        CA::LCFXml::loadFromXml(node,this);
    }
/// human readable to map as pair key value
    void toMap(std::map<std::string,std::string> & outmap,bool ucase=true)
    {
        CA::LCFXml::toMap(outmap,this,ucase);
    }
};


/// implement interface ICAXml_Project : as CAXml_Project
class CAXml_Project
    : public ICAXml_Project
    , public CA::IKeyValue
{
protected:
    CA::keyList predef;

public:
/// ctor
    CAXml_Project();
    ~CAXml_Project();
/// value of this node :
    std::string node_internal_value;
/// object for node : project.build
    CAXml_Project_Build build;
/// value of node : project.name
    std::string name;
/// object for nodes[] : project.patch
    std::vector<CA::IClonable *> patch;
    CAXml_Project_Patch  patch_ref_clonable;
/// object for nodes[] : project.remote
    std::vector<CA::IClonable *> remote;
    CAXml_Project_Remote  remote_ref_clonable;
public:
/// getters
/// return this node name
    inline const CA::_cbt * getICAXml_Name_Value() final
    {
        return mName;
    }

/// return list of predefined childs node name
    inline CA::keyList *  getICAXml_Predef_List() final
    {
        return &predef;
    }

/// load from IXmlNode
    inline void loadFromXml(CA::IXmlNode *node) final
    {
        CA::LCFXml::loadFromXml(node,this);
    }
/// human readable to map as pair key value
    void toMap(std::map<std::string,std::string> & outmap,bool ucase=true)
    {
        CA::LCFXml::toMap(outmap,this,ucase);
    }
/// human readable to string
    void toString(std::iostream &ss) final
    {
        std::string parent("    ");
        ss<<"<"<<getICAXml_Name_Value();
        ss<<">"<<node_internal_value<<std::endl;
        CA::LCFXml::toString(ss,this,parent);
        ss<<"</"<<getICAXml_Name_Value()<<">"<<std::endl;
    }
/// entry point from file xml to variable class members
    bool loadFromXml(std::string filename) final;
};


#endif  //CAPROJECTCONF_HEADER
