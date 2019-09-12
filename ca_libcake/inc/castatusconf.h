#ifndef CASTATUSCONF_HEADER
#define CASTATUSCONF_HEADER

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

/// declare interface ICAXml_Status for node <status>
class ICAXml_Status
{
protected:
   static const CA::_cbt *  caKEY_BUILD;
   static const CA::_cbt *  caKEY_CONFIGURE;
   static const CA::_cbt *  caKEY_DEPLOY;
   static const CA::_cbt *  caKEY_DOWNLOAD;
   static const CA::_cbt *  caKEY_INSTALL;
   static const CA::_cbt *  caKEY_PACKAGE;
   static const CA::_cbt *  caKEY_PATCH;
   static const CA::_cbt *  caKEY_POST_BUILD;
   static const CA::_cbt *  caKEY_POST_CONFIGURE;
   static const CA::_cbt *  caKEY_POST_DEPLOY;
   static const CA::_cbt *  caKEY_POST_DOWNLOAD;
   static const CA::_cbt *  caKEY_POST_INSTALL;
   static const CA::_cbt *  caKEY_POST_PACKAGE;
   static const CA::_cbt *  caKEY_POST_PATCH;
   static const CA::_cbt *  caKEY_POST_SAVE_SOURCE;
   static const CA::_cbt *  caKEY_PRE_BUILD;
   static const CA::_cbt *  caKEY_PRE_CONFIGURE;
   static const CA::_cbt *  caKEY_PRE_DEPLOY;
   static const CA::_cbt *  caKEY_PRE_DOWNLOAD;
   static const CA::_cbt *  caKEY_PRE_INSTALL;
   static const CA::_cbt *  caKEY_PRE_PACKAGE;
   static const CA::_cbt *  caKEY_PRE_PATCH;
   static const CA::_cbt *  caKEY_PRE_SAVE_SOURCE;
   static const CA::_cbt *  caKEY_SAVE_SOURCE;
   static const CA::_cbt *   mName;

public:
    virtual ~ICAXml_Status()=default;
    virtual bool loadFromXml(std::string filename)=0;
    virtual void toString(std::iostream &ss)=0;
};


/// implement interface ICAXml_Status : as CAXml_Status
class CAXml_Status
    : public ICAXml_Status
    , public CA::IKeyValue
{
protected:
    CA::keyList predef;

public:
/// ctor
    CAXml_Status();
/// value of this node : 
   std::string node_internal_value;
/// value of node : status.build
   std::string build;
/// value of node : status.configure
   std::string configure;
/// value of node : status.deploy
   std::string deploy;
/// value of node : status.download
   std::string download;
/// value of node : status.install
   std::string install;
/// value of node : status.package
   std::string package;
/// value of node : status.patch
   std::string patch;
/// value of node : status.post_build
   std::string post_build;
/// value of node : status.post_configure
   std::string post_configure;
/// value of node : status.post_deploy
   std::string post_deploy;
/// value of node : status.post_download
   std::string post_download;
/// value of node : status.post_install
   std::string post_install;
/// value of node : status.post_package
   std::string post_package;
/// value of node : status.post_patch
   std::string post_patch;
/// value of node : status.post_save_source
   std::string post_save_source;
/// value of node : status.pre_build
   std::string pre_build;
/// value of node : status.pre_configure
   std::string pre_configure;
/// value of node : status.pre_deploy
   std::string pre_deploy;
/// value of node : status.pre_download
   std::string pre_download;
/// value of node : status.pre_install
   std::string pre_install;
/// value of node : status.pre_package
   std::string pre_package;
/// value of node : status.pre_patch
   std::string pre_patch;
/// value of node : status.pre_save_source
   std::string pre_save_source;
/// value of node : status.save_source
   std::string save_source;
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


#endif  //CASTATUSCONF_HEADER
