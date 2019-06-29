#ifndef CA_MINI_XML_HEADER
#define CA_MINI_XML_HEADER

/**************************************************************
Copyright(c) 2012-2019 Angelo Coppi

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

#include <cstddef>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <sstream>
#include <iostream>
#include <locale>
#include <chrono>
#include <cstring>

namespace CA
{
#ifdef _DOUBLE_UNICODE
typedef  char32_t     _cbt;
#else
#ifdef _UNICODE
typedef  char16_t     _cbt;
#else
typedef char _cbt;
#endif
#endif

#ifdef _MSV_VER
#include <codecvt>
#endif


#if  (_WIN32 || _WIN64)
#define wctombs wcstombs
#endif

#ifdef _UNICODE

class UtoA
{
public:
    UtoA(const std::u16string & v):_good(false)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>,char16_t> converter;
        if(v.size())
        {
            u8 = converter.to_bytes(v);
            if(u8.size())
            {
                _good=true;
            }
        }
        else
        {
            _good=true;
            u8.clear();
        }
    }
    inline const char *utf8()
    {
        return u8.c_str();
    }
    inline bool good()
    {
        return _good;
    }
private:
    std::string u8;
    bool _good;
};
#else

class UtoA
{
public:
    inline explicit UtoA(const std::string &v)
    {
        u8 = v.c_str();
    }

    inline explicit UtoA(const char *v)
    {
        u8 = v;
    }

    inline const char *utf8()
    {
        return u8;
    }

    inline bool good()
    {
        return true;
    }

private:
    const char *u8;
};

#endif

#ifdef _UNICODE
class AtoU
{
public:
    AtoU(const std::string & v):_good(false)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>,char16_t> converter;
        if(v.size())
        {
            u16 = converter.from_bytes(v);
            if(u16.size())
            {
                _good=true;
            }
        }
        else
        {
            _good=true;
            u16.clear();
        }
    }
    inline const char16_t *utf16()
    {
        return u16.c_str();
    }
    inline bool good()
    {
        return _good;
    }
private:
    std::u16string u16;
    bool _good;
};

#else

class AtoU
{
public:
    inline explicit AtoU(const std::string &v)
    {
        u16 = v.c_str();
    }

    inline explicit AtoU(const char *v)
    {
        u16 = v;
    }

    inline const char *utf16()
    {
        return u16;
    }

    inline bool good()
    {
        return true;
    }

private:
    const char *u16;
};

#endif
class IXmlNode;
typedef std::pair<std::string, std::string> optionPair;
typedef std::map<std::string, std::string> optionsList;
typedef std::pair<std::string,optionsList > pairValue;
typedef std::vector<IXmlNode *> xmlnodeList;


class IXmlNode
{
public:
    static IXmlNode * getNewNode();
    typedef enum tag_imx_node_type
    {
        inode_simple,
        inode_simple_with_options,
        inode_childs,
        inode_childs_with_options,
        inode_array,
        inode_array_with_options,
        inode_array_childs,
        inode_array_childs_with_options,
    } xmlNodeType;
public:


    virtual IXmlNode *find(std::string _name) = 0;

    virtual IXmlNode *add(std::string _name, std::string  value) = 0;

    virtual IXmlNode *add(std::string _name, std::string & value,optionsList & optl) = 0;

    virtual bool remove(std::string name)=0;

    virtual long getLong() = 0;

    virtual std::string &getValue() = 0;

    virtual IXmlNode *getNext() = 0;

    virtual void setNext(IXmlNode *v) = 0;

    virtual const std::string &getName() = 0;

    virtual const std::string &getFullName() = 0;

    virtual void getDecorateName(std::string & out) = 0;

    virtual void getDiscendantDecorateName(std::string & out)=0;

    virtual void setName(std::string _name) = 0;

    virtual IXmlNode *getParent() = 0;

    virtual void setParent(IXmlNode *v) = 0;

    virtual IXmlNode *getChild() = 0;

    virtual void setChild(IXmlNode *v) = 0;

    virtual void setValue(std::string _value) = 0;

    virtual size_t getChildName(std::string name) = 0;

    virtual size_t getChildNameList(std::string name, xmlnodeList *child, IXmlNode ** templ_m) = 0;

    virtual IXmlNode *lastchild() = 0;

    virtual IXmlNode *findLast(std::string _name, IXmlNode *end) = 0;

    virtual IXmlNode *link(std::string &name, IXmlNode *_child) = 0;

    virtual IXmlNode *cat(std::string addValue) = 0;

    virtual void addOption(optionPair & option) = 0;

    virtual optionsList &getOptions() = 0;

    virtual void setOptions( optionsList & optl) = 0;

    virtual void mergeOptions( optionsList & optl) = 0;

    virtual const xmlNodeType getNodeType() = 0;

    virtual void setNodeType(xmlNodeType n)=0;

    virtual size_t getIndex() = 0;

    virtual size_t getChildsNum() =0;

    virtual void merge(IXmlNode *other)=0;

    virtual void setIndex(size_t _index) = 0;

    virtual bool load(std::string file_in)=0;

    virtual bool save(std::string file_out)=0;

    virtual void print(FILE *out, bool decorate=false) = 0;

    virtual void toString(std::stringstream & ss,bool descendant,bool decorate=false)=0;

    virtual ~IXmlNode() = default;
};


///simple xml for key<.key.....> - value pair
/// warning : no replace symbols as standard xml ex < -> &lt
/// warning : unsupport attrib key value
class miniXmlNode
    : public IXmlNode
{
    IXmlNode *parent;    /// the father of this node
    IXmlNode *child;    /// the child of this node
    IXmlNode *next;        /// the next node , child of this father
    std::string fullname;        /// the node fullname as node1.node2.nodexx
    std::string name;        /// the node name
    std::string value;        /// value of this node
    xmlNodeType type;    /// type :simple with chjilds , in array , in array with childs
    size_t index;   /// if array tipe index of
    optionsList options;
protected:
    /// clear the node ..
    void clearNode();
    /// add a node with option
    static IXmlNode *add(IXmlNode * node,const std::string & _name,
                         std::string &_value , optionsList &optl);
    /// remove node
    bool remove(IXmlNode *curr,const std::string & _name);
    /// link a node to anoter
    static IXmlNode *link(IXmlNode * node, const std::string &name, IXmlNode *_child);
    /// print a node
    static void print(FILE *out, miniXmlNode *root,bool decorate);
    /// to strin a node
    static void toString(IXmlNode * node,std::stringstream & ss,bool descendant,bool decorate);
    /// change node type
    static void checkNodeType(IXmlNode * node, bool array);
    /// merge child node from other node
    void merge(IXmlNode *node, IXmlNode *other);
    /// merge option from nodes
    static void mergeOptions(optionsList & curr, optionsList &merge);
    /// load from file
    static bool load(const std::string & file_in, miniXmlNode *root);
    /// save to file
    static bool save(const std::string & file_out, miniXmlNode *root);
    /// get num od childs with name=name
    static size_t getChildName(IXmlNode *node,std::string & name);
    /// get list of childs with name=name
    static size_t getChildNameList(IXmlNode *node, const std::string & name,
                                   xmlnodeList * child, IXmlNode ** templ_m);
    /// get last child
    static IXmlNode *lastchild(IXmlNode *node);
    /// find last next
    static IXmlNode *findLast(IXmlNode *node,const std::string & _name,IXmlNode *end);
    /// fina node with name name
    static IXmlNode *find(IXmlNode *node , const std::string & _name);
    /// compare option
    static bool  compareOption(optionsList &opt1,optionsList &opt2);
    /// ruturn the child with max childs
    static size_t getChildsNum(IXmlNode *node);
    /// print decorated name
    static void getDecorateName(IXmlNode *node, std::string &out);
    /// print decorated name
    static void getDiscendantDecorateName(IXmlNode *node, std::string &out);
public:
    /// defautl ctor
    miniXmlNode(std::string _name, std::string _value,
                IXmlNode *_parent = nullptr, IXmlNode *_child = nullptr,
                IXmlNode *_next = nullptr);

    /// default destructor
    ~miniXmlNode() final;;

    /// add a child node a this node. _name as
    /// xPath for crossing from iinternal child nodes
    /// path separator is assumend the point '.'
    inline IXmlNode *add(std::string name, std::string  value) final
    {
        optionsList optl;
        return miniXmlNode::add(this,name,value,optl);
    }
    /// add a child node with options a this node.
    inline IXmlNode *add(std::string name, std::string & value, optionsList & optl) final
    {
        return miniXmlNode::add(this,name,value,optl);
    }
    /// remove child node
    inline bool remove(std::string name) final
    {
        return remove(this,name);
    }

/// this function link at this node a child xmlNode
    inline IXmlNode *link(std::string &name, IXmlNode *_child) final
    {
        return miniXmlNode::link(this,name,_child);
    }

    /// this function add a value at already existent value
    IXmlNode *cat(std::string addValue) final;

    /// inbox for value, return the current value
    inline std::string &getValue() final
    {
        return value;
    }

    /// inbox for value, return the current value from atol(value)
    long getLong() final;

    /// walking from child , return the child with has next field set a  nullptr pointer
    inline IXmlNode *lastchild() final
    {
        return lastchild(this);
    }

    /// this function return a last next node
    inline IXmlNode *findLast(std::string _name, IXmlNode *end) final
    {
        return miniXmlNode::findLast(this, _name, end);
    }

    inline IXmlNode *find(std::string _name) final
    {
        return miniXmlNode::find(this,_name);
    }

    /// generate a XML file
    inline void print(FILE *out, bool decorate=false) final
    {
        miniXmlNode::print(out,this,decorate);
    }

    inline void toString(std::stringstream &ss,bool descendant,bool decorate=false) final
    {
        miniXmlNode::toString(this,ss,descendant,decorate);
    }

    inline bool load(std::string file_in)final
    {
        return miniXmlNode::load(file_in,this);
    }

    inline bool save(std::string file_out)final
    {
        return miniXmlNode::save(file_out,this);
    }

    /// assign a requested name
    inline void setName(std::string _name) final
    {
        name = _name;
        if(parent!=nullptr)
        {
            fullname=parent->getFullName();
            fullname+=".";
            fullname+=name;
        }
        else {
            fullname = name;
        }
    }

    /// assigne a requested value
    inline void setValue(std::string _value) final
    {
        value = _value;
    }

    /// return num of child with name xx
    inline size_t getChildName(std::string name) final
    {
        return miniXmlNode::getChildName(this,name);
    }

    /// return num and list all childs with name xx
    inline size_t getChildNameList(std::string name, xmlnodeList *child, IXmlNode ** templ_m) final
    {
        return miniXmlNode::getChildNameList(this,name,child,templ_m);
    }

    /// in line return parent
    inline IXmlNode *getParent() final
    {
        return parent;
    }

    inline void setParent(IXmlNode *v) final
    {
        parent = v;
    }

    inline IXmlNode *getChild() final
    {
        return child;
    }

    inline void setChild(IXmlNode *v) final
    {
        child = v;
    }

    inline IXmlNode *getNext() final
    {
        return next;
    }

    inline void setNext(IXmlNode *v) final
    {
        next = v;
    }

    inline const std::string &getName() final
    {
        return const_cast<const std::string &>(name);
    }

    inline const std::string &getFullName() final
    {
        return const_cast<const std::string &>(fullname);
    }

    inline void getDecorateName(std::string & out) final
    {
        getDecorateName(this,out);
    }

    inline void getDiscendantDecorateName(std::string & out) final
    {
        getDiscendantDecorateName(this,out);
    }

    void addOption(optionPair & option) final;


    inline  optionsList &getOptions() final
    {
        return options;
    }


    inline void setOptions( optionsList & optl) final
    {
        options.clear();
        options=optl;
        checkNodeType(this, false);
    }

    inline void mergeOptions( optionsList & optl) final
    {
        mergeOptions(this->options,optl);
        checkNodeType(this, false);
    }

    inline void merge(IXmlNode *other) final
    {
        merge(this,other);
        checkNodeType(this, false);
    };

    inline const xmlNodeType getNodeType() final
    {
        return type;
    }

    inline void setNodeType(xmlNodeType n) final
    {
        type=n;
    }

    /// get index if array type
    inline size_t getIndex() final
    {
        return index;
    }

    inline size_t getChildsNum() final
    {
        return getChildsNum(this);
    }

    /// get index if array type
    inline void setIndex(size_t _index) final
    {
        index = _index;
    }

    friend bool swapNode(miniXmlNode *src, miniXmlNode *dst);

};


class miniXmlParse
{
    miniXmlNode *root; ///out
    std::string filebuff;
    std::string::iterator p_index;
    std::string::iterator p_last;
    std::string::iterator p_start;
    std::string::iterator p_end;
public:
    miniXmlParse(const std::string & filename, miniXmlNode *_root);

    ~miniXmlParse();

    bool parse();

protected:
    bool findNextChar(_cbt ch);

    bool getTokens(miniXmlNode **currrent, bool *firstNode);

    bool captureToken(std::string &token, optionsList & optl, bool &skipvalue);

    bool captureToken(std::string &token);

    bool captureValue(std::string &token);

    void captureOption(std::string &token, optionsList & optl);

    bool skipSpaces(bool space = false);

    inline bool isEnd()
    {
        return (p_index != p_end);
    }
};


}


#endif