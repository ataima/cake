#ifndef CALAYERCONF_HEADER
#define CALAYERCONF_HEADER

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

/// declare interface ICAXml_Layer_Maxtask for node <maxtask>
class ICAXml_Layer_Maxtask
{
protected:
    static const CA::_cbt *  caKEY_BUILD;
    static const CA::_cbt *  caKEY_DEPLOY;
    static const CA::_cbt *  caKEY_PACKAGE;
    static const CA::_cbt *  caKEY_SOURCE;
    static const CA::_cbt *   mName;

public:
    virtual ~ICAXml_Layer_Maxtask()=default;
};


/// declare interface ICAXml_Layer for node <layer>
class ICAXml_Layer
{
protected:
    static const CA::_cbt *  caKEY_INCLUDE;
    static const CA::_cbt *  caKEY_INFO;
    static const CA::_cbt *  caKEY_MAXTASK;
    static const CA::_cbt *  caKEY_NAME;
    static const CA::_cbt *   mName;

public:
    virtual ~ICAXml_Layer()=default;
    virtual bool loadFromXml(std::string filename)=0;
    virtual void toString(std::iostream &ss)=0;
};


/// implement interface ICAXml_Layer_Maxtask : as CAXml_Layer_Maxtask
class CAXml_Layer_Maxtask
    : public ICAXml_Layer_Maxtask
    , public CA::IKeyValue
{
protected:
    CA::keyList predef;

public:
/// ctor
    CAXml_Layer_Maxtask();
/// value of this node :
    std::string node_internal_value;
/// value of node : layer.maxtask.build
    std::string build;
/// value of node : layer.maxtask.deploy
    std::string deploy;
/// value of node : layer.maxtask.package
    std::string package;
/// value of node : layer.maxtask.source
    std::string source;
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


/// implement interface ICAXml_Layer : as CAXml_Layer
class CAXml_Layer
    : public ICAXml_Layer
    , public CA::IKeyValue
{
protected:
    CA::keyList predef;

public:
/// ctor
    CAXml_Layer();
/// value of this node :
    std::string node_internal_value;
/// value of nodes[] : layer.include
    std::vector<std::string> include;
/// value of node : layer.info
    std::string info;
/// object for node : layer.maxtask
    CAXml_Layer_Maxtask maxtask;
/// value of node : layer.name
    std::string name;
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


#endif  //CALAYERCONF_HEADER
