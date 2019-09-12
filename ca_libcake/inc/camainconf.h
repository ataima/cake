#ifndef CAMAINCONF_HEADER
#define CAMAINCONF_HEADER

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

/// declare interface ICAXml_Main_Defaults_Step_User_env for node <user_env>
class ICAXml_Main_Defaults_Step_User_env
{
protected:
   static const CA::_cbt *  caKEY_NAME;
   static const CA::_cbt *  caKEY_VALUE;
   static const CA::_cbt *   mName;

public:
    virtual ~ICAXml_Main_Defaults_Step_User_env()=default;
};


/// declare interface ICAXml_Main_Defaults_Step for node <step>
class ICAXml_Main_Defaults_Step
{
protected:
   static const CA::_cbt *  caKEY_AR;
   static const CA::_cbt *  caKEY_ARCH;
   static const CA::_cbt *  caKEY_AS;
   static const CA::_cbt *  caKEY_ASFLAGS;
   static const CA::_cbt *  caKEY_C_INCLUDE_PATH;
   static const CA::_cbt *  caKEY_CC;
   static const CA::_cbt *  caKEY_CFLAGS;
   static const CA::_cbt *  caKEY_CPATH;
   static const CA::_cbt *  caKEY_CPLUS_INCLUDE_PATH;
   static const CA::_cbt *  caKEY_CPPFLAGS;
   static const CA::_cbt *  caKEY_CROSS;
   static const CA::_cbt *  caKEY_CXX;
   static const CA::_cbt *  caKEY_CXXFLAGS;
   static const CA::_cbt *  caKEY_ENABLE;
   static const CA::_cbt *  caKEY_ID;
   static const CA::_cbt *  caKEY_INFO;
   static const CA::_cbt *  caKEY_LAYER;
   static const CA::_cbt *  caKEY_LD;
   static const CA::_cbt *  caKEY_LDFLAGS;
   static const CA::_cbt *  caKEY_LIBS;
   static const CA::_cbt *  caKEY_NAME;
   static const CA::_cbt *  caKEY_NM;
   static const CA::_cbt *  caKEY_PACKAGES;
   static const CA::_cbt *  caKEY_STRIP;
   static const CA::_cbt *  caKEY_USER_ENV;
   static const CA::_cbt *   mName;

public:
    virtual ~ICAXml_Main_Defaults_Step()=default;
};


/// declare interface ICAXml_Main_Defaults for node <defaults>
class ICAXml_Main_Defaults
{
protected:
   static const CA::_cbt *  caKEY_STEP;
   static const CA::_cbt *   mName;

public:
    virtual ~ICAXml_Main_Defaults()=default;
};


/// declare interface ICAXml_Main_Conf for node <conf>
class ICAXml_Main_Conf
{
protected:
   static const CA::_cbt *  caKEY_BUILD;
   static const CA::_cbt *  caKEY_IMAGES;
   static const CA::_cbt *  caKEY_LD_LIBRARY_PATH;
   static const CA::_cbt *  caKEY_LOGS;
   static const CA::_cbt *  caKEY_PATH;
   static const CA::_cbt *  caKEY_ROOT;
   static const CA::_cbt *  caKEY_SCRIPTS;
   static const CA::_cbt *  caKEY_SOURCES;
   static const CA::_cbt *  caKEY_STATUS;
   static const CA::_cbt *  caKEY_STORE;
   static const CA::_cbt *   mName;

public:
    virtual ~ICAXml_Main_Conf()=default;
};


/// declare interface ICAXml_Main for node <main>
class ICAXml_Main
{
protected:
   static const CA::_cbt *  caKEY_CONF;
   static const CA::_cbt *  caKEY_DEFAULTS;
   static const CA::_cbt *   mName;

public:
    virtual ~ICAXml_Main()=default;
    virtual bool loadFromXml(std::string filename)=0;
    virtual void toString(std::iostream &ss)=0;
};


/// implement interface ICAXml_Main_Defaults_Step_User_env : as CAXml_Main_Defaults_Step_User_env
class CAXml_Main_Defaults_Step_User_env
    : public ICAXml_Main_Defaults_Step_User_env
    , public CA::IClonableOption
{
protected:
    CA::keyList predef;

public:
/// ctor
    CAXml_Main_Defaults_Step_User_env();
/// value of this node : 
   std::string node_internal_value;
/// options of this node : 
   CA::optionsList node_internal_options;
/// value of node : main.defaults.step.user_env.name
   std::string name;
/// value of node : main.defaults.step.user_env.value
   std::string value;
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
        return new CAXml_Main_Defaults_Step_User_env();
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
      if(!optl.empty()){
          auto it=optl.begin();
          auto _end=optl.end();
          while(it!=_end) {
              CA::optionPair p(it->first,it->second);
              node_internal_options.insert(p);
              it++;
          }
       }
    }
};


/// implement interface ICAXml_Main_Defaults_Step : as CAXml_Main_Defaults_Step
class CAXml_Main_Defaults_Step
    : public ICAXml_Main_Defaults_Step
    , public CA::IClonable
{
protected:
    CA::keyList predef;

public:
/// ctor
    CAXml_Main_Defaults_Step();
/// value of this node : 
   std::string node_internal_value;
/// value of node : main.defaults.step.ar
   std::string ar;
/// value of node : main.defaults.step.arch
   std::string arch;
/// value of node : main.defaults.step.as
   std::string as;
/// value of node : main.defaults.step.asflags
   std::string asflags;
/// value of node : main.defaults.step.c_include_path
   std::string c_include_path;
/// value of node : main.defaults.step.cc
   std::string cc;
/// value of node : main.defaults.step.cflags
   std::string cflags;
/// value of node : main.defaults.step.cpath
   std::string cpath;
/// value of node : main.defaults.step.cplus_include_path
   std::string cplus_include_path;
/// value of node : main.defaults.step.cppflags
   std::string cppflags;
/// value of node : main.defaults.step.cross
   std::string cross;
/// value of node : main.defaults.step.cxx
   std::string cxx;
/// value of node : main.defaults.step.cxxflags
   std::string cxxflags;
/// value of node : main.defaults.step.enable
   std::string enable;
/// value of node : main.defaults.step.id
   std::string id;
/// value of node : main.defaults.step.info
   std::string info;
/// value of node : main.defaults.step.layer
   std::string layer;
/// value of node : main.defaults.step.ld
   std::string ld;
/// value of node : main.defaults.step.ldflags
   std::string ldflags;
/// value of node : main.defaults.step.libs
   std::string libs;
/// value of node : main.defaults.step.name
   std::string name;
/// value of node : main.defaults.step.nm
   std::string nm;
/// value of node : main.defaults.step.packages
   std::string packages;
/// value of node : main.defaults.step.strip
   std::string strip;
/// object for nodes[] : main.defaults.step.user_env
   std::vector<CA::IClonableOption *> user_env;
   CAXml_Main_Defaults_Step_User_env  user_env_ref_clonable_option;
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
        return new CAXml_Main_Defaults_Step();
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


/// implement interface ICAXml_Main_Defaults : as CAXml_Main_Defaults
class CAXml_Main_Defaults
    : public ICAXml_Main_Defaults
    , public CA::IKeyValue
{
protected:
    CA::keyList predef;

public:
/// ctor
    CAXml_Main_Defaults();
/// value of this node : 
   std::string node_internal_value;
/// object for nodes[] : main.defaults.step
   std::vector<CA::IClonable *> step;
   CAXml_Main_Defaults_Step  step_ref_clonable;
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


/// implement interface ICAXml_Main_Conf : as CAXml_Main_Conf
class CAXml_Main_Conf
    : public ICAXml_Main_Conf
    , public CA::IKeyValue
{
protected:
    CA::keyList predef;

public:
/// ctor
    CAXml_Main_Conf();
/// value of this node : 
   std::string node_internal_value;
/// value of node : main.conf.build
   std::string build;
/// value of node : main.conf.images
   std::string images;
/// value of node : main.conf.ld_library_path
   std::string ld_library_path;
/// value of node : main.conf.logs
   std::string logs;
/// value of node : main.conf.path
   std::string path;
/// value of node : main.conf.root
   std::string root;
/// value of node : main.conf.scripts
   std::string scripts;
/// value of node : main.conf.sources
   std::string sources;
/// value of node : main.conf.status
   std::string status;
/// value of node : main.conf.store
   std::string store;
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


/// implement interface ICAXml_Main : as CAXml_Main
class CAXml_Main
    : public ICAXml_Main
    , public CA::IKeyValue
{
protected:
    CA::keyList predef;

public:
/// ctor
    CAXml_Main();
/// value of this node : 
   std::string node_internal_value;
/// object for node : main.conf
   CAXml_Main_Conf conf;
/// object for node : main.defaults
   CAXml_Main_Defaults defaults;
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


#endif  //CAMAINCONF_HEADER
