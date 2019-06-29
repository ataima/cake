#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale>
#include <string>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "caminiXml.h"
#include <iostream>


#ifndef _MSC_VER

#include <unistd.h>

#endif


#define DEBUG_XML 0

/**************************************************************
Copyright(c) 2015 Angelo Coppi
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

#if defined(_MSC_VER ) && defined(_UNICODE)
std::locale::id std::codecvt<char16_t, char, struct _Mbstatet>::id;
#endif

namespace CA
{


IXmlNode * IXmlNode::getNewNode()
{
    return new miniXmlNode("","");
}



miniXmlNode::miniXmlNode(const std::string _name, const std::string _value,
                         IXmlNode *_parent, IXmlNode *_child, IXmlNode *_next)
    : parent(_parent),
      child(_child),
      next(_next),
      name(_name),
      value(_value),
      type(xmlNodeType::inode_simple),
      index(0)
{
    if (parent != nullptr && parent->getChild() == nullptr)
        parent->setChild(this);
    else if (parent != nullptr && parent->getChild() != nullptr)
    {
        IXmlNode *n = parent->getChild();
        IXmlNode *t = parent->getChild();
        while (t != nullptr)
        {
            n = t;
            t = t->getNext();
        }
        n->setNext( this );
    }
    if(parent == nullptr)
    {
        fullname = name;
    }
    else
    {
        fullname = parent->getFullName() + ".";
        fullname+=name;
    }
    checkNodeType(this,false);
}
/// default destructor

miniXmlNode::~miniXmlNode()
{
    clearNode();
}

void miniXmlNode::clearNode()
{
    // cancella tutta la catena
    delete child;
    child = nullptr;
    delete next;
    next = nullptr;
}

void miniXmlNode::addOption(optionPair & option)
{
    for (auto it : options )
    {
        if(it.first==option.first)
        {
            std::stringstream error;
            error<<"In "<<getName()<<" : option "<<it.first<<
                 "already present with value : "<< it.second<<std::endl<<
                 "Cannot assign new option : " <<option.first<< " with value : "<<
                 option.second<<std::endl;
            throw std::runtime_error(error.str().c_str());
        }
    }
    options.insert(option);
}


void miniXmlNode::checkNodeType(IXmlNode *curr,bool array)
{

    if(array)
    {
        curr->setNodeType(inode_array);
        if(!curr->getOptions().empty())
            curr->setNodeType(inode_array_with_options);
        if(curr->getChild()!=nullptr)
        {
            curr->setNodeType(inode_array_childs);
            if(!curr->getOptions().empty())
                curr->setNodeType(inode_array_childs_with_options);
        }
    }
    else
    {

        switch(curr->getNodeType())
        {
        case inode_simple:
            if(!curr->getOptions().empty())
                curr->setNodeType(inode_simple_with_options);
            if(curr->getChild()!=nullptr)
            {
                curr->setNodeType(inode_childs);
                if(!curr->getOptions().empty())
                    curr->setNodeType(inode_childs_with_options);
            }
            break;
        case inode_simple_with_options:
            if(curr->getChild()!=nullptr)
            {
                curr->setNodeType(inode_childs_with_options);
            }
            break;
        case inode_childs:
            if(!curr->getOptions().empty())
                curr->setNodeType(inode_childs_with_options);
            break;
        case  inode_childs_with_options:
            break;
        case inode_array:
            if(!curr->getOptions().empty())
                curr->setNodeType(inode_array_with_options);
            if(curr->getChild()!=nullptr)
            {
                curr->setNodeType(inode_array_childs);
                if(!curr->getOptions().empty())
                    curr->setNodeType(inode_array_childs_with_options);
            }
            break;
        case inode_array_with_options:
            if(curr->getChild()!=nullptr)
            {
                curr->setNodeType(inode_array_childs_with_options);
            }
            break;
        case inode_array_childs:
            if(!curr->getOptions().empty())
                curr->setNodeType(inode_array_childs_with_options);
            break;
        case  inode_array_childs_with_options:
            break;
        }
    }
    ///std::cout<<">     N:"<<curr->getName()<<" - T:"<<curr->getNodeType()<<std::endl;
}


///if child node of other node is missing in 'node' add the child node
void  miniXmlNode::merge(IXmlNode *node, IXmlNode *other)
{
    if (node->getFullName() == other->getFullName())
    {
        // get full list of child of other node
        xmlnodeList childs;
        auto nnode = getChildNameList(other, "*", &childs, nullptr);
        if (nnode > 0)
        {
            for (auto it : childs)
            {
                auto nt = getChildNameList(node, it->getName(), nullptr, nullptr);
                if (nt == 0)
                {
                    node->add(it->getName(), it->getValue(), it->getOptions());
                }
            }
        }
    }
}

void miniXmlNode::mergeOptions(optionsList & curr, optionsList &merge)
{
    if(!merge.empty())
    {
        for (auto & it : merge )
        {
            auto v = curr.find(it.first);
            if (v == curr.end())
                curr.insert(it);
            else
            {
                v->second=it.second;
            }
        }
    }
}



bool  miniXmlNode::compareOption(optionsList &opt1,optionsList &opt2)
{
    // true if equals
    if(opt1.size()!=opt2.size())return false;
    auto it1=opt1.begin();
    auto it2=opt2.begin();
    auto stop=opt1.end();
    while(it1!=stop)
    {
        if(it1->first!=it2->first)return false;
        if(it1->second!=it2->second)return false;
        it1++;
        it2++;
    }
    return true;
}


size_t miniXmlNode::getChildsNum(IXmlNode *node)
{
    size_t res=0;
    auto tmp=node->getChild();
    while (tmp!=nullptr)
    {
        res++;
        tmp = tmp->getNext();
    }
    return res;
}


IXmlNode *miniXmlNode::add(IXmlNode *curr,const std::string & _name,
                           std::string & _value , optionsList &optl)
{
    // name as Xpath = A.B.C. es test.suite.doc
    std::string::size_type p = _name.find('.');
    if (p==std::string::npos)
    {
        IXmlNode *newnode;
        if (curr->getChild() == nullptr)
        {
            newnode= new miniXmlNode(_name, _value, curr, nullptr, curr->lastchild());
            if(!optl.empty())newnode->setOptions(optl);
            checkNodeType(curr,false);
            newnode->setIndex(0);
            return newnode;
        }
        else
        {
            IXmlNode *it = curr->find(_name);
            if (it != nullptr )
            {
                checkNodeType(it,true);
                newnode= new miniXmlNode(_name, _value, curr, nullptr, nullptr);
                if(!optl.empty())newnode->setOptions(optl);
                checkNodeType(newnode,true);
                IXmlNode *last=curr->getChild()->findLast(_name,newnode);
                newnode->setIndex(last->getIndex() + 1);
                return newnode;
            }
            else
            {
                newnode= new miniXmlNode(_name, _value, curr, nullptr, nullptr);
                if(!optl.empty())newnode->setOptions(optl);
                checkNodeType(newnode,false);
                newnode->setIndex(0);
                return newnode;
            }
        }
    }
    else
    {
        // has Xpath
        optionsList tmlist;
        std::string start, remain;
        std::string::size_type i;
        for(i=0; i<p; i++)start+=_name[i];
        for(i=p+1; i<_name.size(); i++)remain+=_name[i];
        std::string uu;
        IXmlNode *it = curr->find(start);
        if(it==nullptr)
            it = curr->add(start, uu,tmlist);
        return it->add(remain, _value);
    }
}


bool miniXmlNode::remove(IXmlNode *curr,const std::string & _name)
{
    auto res=false;
    if(curr->getChild()==nullptr)return res;
    else
    {
        auto tmp=curr->getChild();
        if(tmp->getName()==_name)
        {
            if(tmp->getNext()!=nullptr)
            {
                curr->setChild(tmp->getNext());
            }
            else curr->setChild(nullptr);
            delete tmp;
            res=true;
        }
        else
        {
            do
            {
                auto pre=tmp;
                tmp=tmp->getNext();
                if(tmp->getName()==_name)
                {
                    pre->setNext(tmp->getNext());
                    delete tmp;
                    res=true;
                    break;
                }
            }
            while(tmp!=nullptr);
        }
    }
    return res;
}
IXmlNode * miniXmlNode::link(IXmlNode *curr,const std::string & _name, IXmlNode *_child)
{
    IXmlNode *res = curr->find(_name);
    if (res != nullptr)
    {
        if (res->getChild() != nullptr)
            res->lastchild()->setNext( _child );
        else
            res->setChild( _child );
    }
    return res;
}
/// this function add a value at already existent value

IXmlNode *miniXmlNode::cat(std::string addValue)
{
    value += '\r';
    value += '\n';
    value += addValue;
    return this;
}
/// inbox for value, return the current value



long miniXmlNode::getLong()
{
    std::string v = value;
    UtoA toA(v);
    return ::strtol(toA.utf8(),nullptr,10);
}
/// walking from child , return the child with has next field set a  nullptr pointer

IXmlNode *miniXmlNode::lastchild(IXmlNode *curr)
{
    IXmlNode *first = curr->getChild();
    if (first != nullptr)
    {
        while (true)
        {
            IXmlNode *_next = first->getNext();
            if (_next == nullptr)return first;
            first = _next;
        }
    }
    return nullptr;
}




IXmlNode *miniXmlNode::findLast(IXmlNode *curr,const std::string & _name,IXmlNode *end)
{
    IXmlNode *res = end;
    IXmlNode *tmp = curr->getNext();
    while(tmp!=nullptr &&  tmp!=end)
    {
        if(tmp->getName()==_name)
            res=tmp;
        tmp=tmp->getNext();
    }
    return res;
}




IXmlNode *miniXmlNode::find(IXmlNode *curr,const std::string & _name)
{
    std::string::size_type p = _name.find('.');
    if (p==std::string::npos)
    {
        IXmlNode *res = nullptr;
        xmlnodeList childs;
        auto nnode = getChildNameList(curr, _name, &childs, nullptr);
        if (nnode > 0)
        {
            res = childs.front();
        }
        return res;
    }
    else
    {
        // has Xpath
        std::string start, remain;
        std::string::size_type i;
        for(i=0; i<p; i++)start+=_name[i];
        for(i=p+1; i<_name.size(); i++)remain+=_name[i];
        if( curr->getName()!=start)
        {
            IXmlNode *it = curr->find(start);
            if (it != nullptr)
                return it->find(remain);
            else
                return nullptr;
        }
        else
        {
            return curr->find(remain);
        }
    }
}




/// generate a XML file

void miniXmlNode::print(FILE *out,miniXmlNode *node,bool decorate)
{
    std::stringstream ss;
    node->toString(ss,true,decorate);
    fwrite(ss.str().c_str(), ss.str().size(), sizeof (_cbt), out);
    ss.str("");
}

bool miniXmlNode::load( const std::string & file_in, miniXmlNode *root)
{
    auto res = false;
    if (root != nullptr)
    {
        miniXmlParse parser(file_in, root);
        res = parser.parse();
    }
    return res;
}


void miniXmlNode::toString(IXmlNode *node,std::stringstream & ss,bool descendant,bool decorate)
{
    if (!node->getName().empty()  )
    {
        // name not set ->only container
        if(decorate)
        {
            std::string decoratename;
            node->getDiscendantDecorateName(decoratename);
            ss<<"<!-- "<<decoratename<< " --!>"<<std::endl;
        }
        if(node->getOptions().empty())
        {
            if(node->getValue().empty() && node->getChild()==nullptr)
            {
                ss << "<" << node->getName() << "/>" << std::endl;
            }
            else
            {
                ss << "<" << node->getName() << ">" << std::endl;
            }
        }
        else
        {
            ss << "<" << node->getName();
            for (auto & it : node->getOptions() )
            {
                ss<< " "<<it.first<<"=\""<<it.second<<"\" ";
            }
            if(node->getValue().empty() && node->getChild()==nullptr)
            {
                ss<<"/>"<<std::endl;
            }
            else
            {
                ss<<">"<<std::endl;
            }
        }
#if REPLACE_SYMBOL_XML
        // TODO: this implementation is gabbage
        if (value.size()>0)
        {
            const XCHAR * as[] = { " &lt; ", " &gt; ", " &amp; ", " &apos; ", " &quot; ", " " };
            int len = STRLEN(value);
            int i;
            for (i = 0; i < len; i++)
            {
                //	&lt;	<	less than
                //	&gt;	>	greater than
                //	&amp;	&	ampersand
                //	&apos;	'	apostrophe
                //	&quot;	"	quotation mark
                switch (value[i])
                {
                case '&':
                    fwrite(as[2], 7, sizeof(char), out);
                    break;
                case '\'':
                    fwrite(as[3], 8, sizeof(char), out);
                    break;
                case '"':
                    fwrite(as[4], 8, sizeof(char), out);
                    break;
                case '<':
                    fwrite(as[0], 6, sizeof(char), out);
                    break;
                case '>':
                    fwrite(as[1], 6, sizeof(char), out);
                    break;
                case '\r':
                case '\n':
                    fwrite(as[5], 1, sizeof(char), out);
                    break;
                default:
                    fwrite(&value[i], 1, sizeof(char), out);
                    break;
                }
            }
            fwrite("\n", 1, sizeof(char), out);
        }
#endif
        if (!node->getValue().empty())
        {
            ss << node->getValue() << std::endl;
        }
    }
    else
    {
        if(decorate)
        {
            ss<<"<!-- MAIN ROOT --!>"<<std::endl;
        }
    }
    if(descendant)
    {
        if (node->getChild() != nullptr)
            node->getChild()->toString(ss, descendant,decorate);
        if (!node->getValue().empty() || node->getChild() != nullptr)
        {
            if(!node->getName().empty())
                ss << "</" << node->getName() << ">"<<std::endl;
        }
        if (node->getNext() != nullptr)
            node->getNext()->toString(ss,descendant,decorate);
    }

}


bool miniXmlNode::save( const std::string & fileout, miniXmlNode *root)
{
    auto res = false;
    if (!fileout.empty()  && root != nullptr)
    {
        UtoA toA(fileout);
        FILE *_fout = fopen(toA.utf8(), "wb");
        if (_fout != nullptr)
        {
            root->print(_fout);
            fclose(_fout);
            res=true;
        }
        else
        {
            std::stringstream error;
            error<<"Cannot create output file "<<fileout<<std::endl;
            throw std::runtime_error(error.str().c_str());
        }
    }
    return res;
}


/// assigne a requested value



size_t miniXmlNode::getChildName(IXmlNode *curr,std::string & _name)
{
    size_t res=0;
    if(!curr->getName().empty())
    {
        if(curr->getChild()!=nullptr)
        {
            IXmlNode *tmpnode=curr->getChild();
            do
            {
                if(tmpnode->getName()==_name)res++;
                tmpnode=tmpnode->getNext();
            }
            while(tmpnode!=nullptr);
        }
    }
    return res;
}

// templ_m : return node with max child or with same child but max attribute num
size_t miniXmlNode::getChildNameList(IXmlNode *curr,const std::string &name,
                                     xmlnodeList * list_childs, IXmlNode ** templ_m)
{
    size_t res=0;
    size_t max_child=0;
    if(!curr->getName().empty())
    {
        if(curr->getChild()!=nullptr)
        {
            IXmlNode *tmpnode=curr->getChild();
            if(list_childs!=nullptr)
                list_childs->clear();
            if(templ_m!=nullptr)
                *templ_m=nullptr;
            do
            {
                if(tmpnode->getName()==name || name=="*")
                {
                    if(templ_m!=nullptr)
                    {
                        auto nchild=tmpnode->getChildsNum();
                        if(nchild>max_child)
                        {
                            max_child=nchild;
                            *templ_m = tmpnode;
                        }
                        if((*templ_m)!=nullptr)
                        {
                            if(!tmpnode->getOptions().empty())
                            {
                                (*templ_m)->mergeOptions(tmpnode->getOptions());
                            }
                        }
                    }
                    res++;
                    if(list_childs!=nullptr)
                        list_childs->push_back(tmpnode);
                }
                tmpnode=tmpnode->getNext();
            }
            while(tmpnode!=nullptr);
        }
    }
    return res;
}

void miniXmlNode::getDecorateName(IXmlNode *node, std::string &out)
{
    std::stringstream ss;
    ss<<"("<<node->getName();
    if(node->getIndex()!=0)ss<<"["<<node->getIndex()<<"]";
    for  (auto & it : node->getOptions() )
    {
        ss<<" "<<it.first<<"=\""<<it.second<<"\" ";
    }
    ss<<")";
    out= ss.str();
}


void miniXmlNode::getDiscendantDecorateName(IXmlNode *node, std::string &out)
{
    IXmlNode *tmp=node;
    std::list<std::string > all;
    out.clear();
    while(tmp!=nullptr)
    {
        std::string deco;
        tmp->getDecorateName(deco);
        all.push_front(deco);
        tmp=tmp->getParent();
        if(tmp!= nullptr)
            all.push_front(".");
    }
    if(!all.empty())
    {
        auto it=all.begin();
        auto stop=all.end();
        while(it!=stop)
        {
            out+=*it;
            it++;
        }
    }
}

bool swapNode(miniXmlNode *src, miniXmlNode *dst)
{
    auto res = false;
    if (src == dst)
        return true;
    if (src != nullptr && dst != nullptr)
    {
        dst->name = src->name;
        dst->value = src->value;
        dst->setChild(src->getChild());
        dst->setNext(src->getNext());
        dst->parent = src->parent;
        src->name = "";
        src->value = "";
        src->setChild(nullptr);
        src->setNext(nullptr);
        src->setParent(nullptr);
        dst->getChild()->setParent(dst);
        IXmlNode *next_node = dst->getNext();
        while (next_node != nullptr)
        {
            next_node->setParent(dst);
            next_node = next_node->getNext();
        }
        res = true;
    }
    return res;
}




/////////////////////////file_out///////////////////////////////////////////////////////

miniXmlParse::miniXmlParse(const std::string & _in, miniXmlNode *_root)
{
    if (!_in.empty()  && _root != nullptr)
    {
        root = _root;
        UtoA toA(_in);
        try
        {
            //try as  external file..
            FILE *in = fopen(toA.utf8(), "rb");
            if (in != nullptr)
            {
                fseek(in, 0L, SEEK_END);
                ssize_t lenght = ftell(in);
                fseek(in, 0L, SEEK_SET);
                if (lenght > 0)
                {
                    _cbt *buff = new _cbt[lenght];

                    size_t max_size = fread(buff, sizeof (_cbt), lenght, in);
                    if (max_size > 0)
                    {
                        filebuff.assign((const _cbt *) buff,
                                        (std::string::size_type) max_size / sizeof (_cbt));
                        p_index = filebuff.begin();
                        p_start = p_index;
                        p_last=p_start;
                        p_end = filebuff.end();
                    }
                }
                fclose(in);
            }
            else
            {
                root = nullptr;
                filebuff.clear();
                p_index = filebuff.begin();
                p_start=p_index;
                p_last=p_start;
                p_end = filebuff.end();
            }

        }
        catch (...)
        {
            std::stringstream error;
            error<<"Unknow input file "<<_in<<std::endl;
            throw std::runtime_error(error.str().c_str());
        }
    }
    else
    {
        root = nullptr;
        p_index = filebuff.begin();
        p_start=p_index;
        p_last=p_start;
        p_end = filebuff.end();
    }

}

miniXmlParse::~miniXmlParse()
{
    filebuff.clear();
}

bool miniXmlParse::getTokens(miniXmlNode **node, bool *firstNode)
{
    if (*node != nullptr && firstNode != nullptr)
    {
        std::string token_name;
        std::string token_value;
        optionsList token_options;
        std::string::iterator p_temp = p_index;
        bool skipvalue;
        skipSpaces(true);
        if (*p_index == '<')
        {
            p_index++;
            if (*p_index == '/')
            {
                //end previous token
                p_index = p_temp;
                return false;
            }
            else if (*p_index == '?')
            {
                //"<?......?>
                p_index++;
                while(p_index<p_end && *p_index!='?')p_index++;
                p_index++;
                if(*p_index=='>')p_index++;
                return  getTokens(node,firstNode);
            }
            else if (*p_index == '!')
            {
                //"<!......> ignore -- or CADATA ..DOCTYPE ETC
                p_index++;
                auto i=0;
                std::string mm;
                while(p_index<p_end && *p_index!='>' && i < 7)
                {
                    mm+=*p_index;
                    p_index++;
                    i++;
                }
                if(mm=="[CDATA[")
                {
                    while(p_index<p_end && *p_index!=']' )p_index++;
                    mm.clear();
                    mm+=*p_index;
                    p_index++;
                    mm+=*p_index;
                    p_index++;
                    mm+=*p_index;
                    if(mm!="]]>")
                    {
                        std::string msg;
                        while(p_last<p_index)
                        {
                            msg += *p_last;
                            p_last++;
                        }
                        std::stringstream ss;
                        ss<<"Missing CDATA closure : "<<(size_t)(p_index-p_start)<<
                          " '"<<msg<<"' "<<std::endl;
                        throw std::runtime_error ( ss.str().c_str());
                    }
                }
                else
                    while(p_index<p_end && *p_index!='>' )p_index++;
                p_index++;
                skipSpaces(true);
                return  getTokens(node,firstNode);
            }
            else
            {
                p_index = p_temp;
            }
        }

        if (findNextChar('<'))
        {
            if (captureToken(token_name,token_options,skipvalue))
            {
                if(!skipvalue)
                {
                    skipSpaces();
                    captureValue(token_value);
                }
                else
                {
                    token_value.clear();
                }
                if (isEnd())
                {
#if DEBUG_XML
                    if(token_option.empty())
                    {
                        std::cout<<(*node)->getName()<<" : "<<token_name<<" = '"<<token_value<<"'"<<std::endl;
                    }
                    else
                    {
                        std::cout<<(*node)->getName()<<" : "<<token_name<<" = '"<<token_value<<"' opt='"<<
                                 token_option<<"' '"<<token_option_value<<"'"<<std::endl;
                    }
#endif
                    //miniXmlNode *oldPos = *node;
                    if (!*firstNode)
                    {
                        (*firstNode) = true;
                        if (!token_name.empty())
                            (*node)->setName(token_name);
                        if (!token_value.empty())
                            (*node)->setValue(token_value);
                        if(!token_options.empty())
                            (*node)->setOptions(token_options);
                        if(skipvalue)
                        {
                            skipSpaces(true);
                            return true;
                        }
                    }
                    else
                    {
                        *node = dynamic_cast<miniXmlNode *> (
                                    (*node)->add(token_name,
                                                 token_value,token_options));
                        if(skipvalue)
                        {
                            skipSpaces(true);
                            return true;
                        }
                    }
                    while (getTokens(node, firstNode))
                    {
                        *node = dynamic_cast<miniXmlNode *> ((*node)->getParent());
                        p_last=p_index;
                    }
                }

            }
        }
        if (*p_index == '<')
        {
            p_index++;
            if (*p_index == '/')
            {
                //end previous token
                p_index++;
                if (skipSpaces())
                {
                    token_value.clear();
                    captureToken(token_value);
                    skipSpaces(true);
                    if (token_value == (*node)->getName())
                        return true;
                    else
                    {
                        std::stringstream ss;
                        ss<<"Missmatch node closure : </"<< token_value<<"> must be </"
                          <<(*node)->getName()<<"> ("<<(*node)->getFullName()<<")"<<std::endl;
                        throw std::runtime_error(ss.str().c_str());
                    }
                }
            }
        }
    }
    return false;
}

bool miniXmlParse::findNextChar(_cbt ch)
{
    while (*p_index != ch && p_index < p_end)
        p_index++;
    p_index++;

    return isEnd();
}


void miniXmlParse::captureOption(   std::string & token,
                                    optionsList & optl)
{
    while(true)
    {
        std::string _option_name,_option_value;
        while (*p_index == ' ' && *p_index != '/' && *p_index != '>' && p_index < p_end)p_index++;
        if (*p_index == '/')
            return;
        if (*p_index == '>')return;
        while (*p_index != '=' && *p_index != '>' && p_index < p_end)
        {
            if (*p_index > ' ') _option_name.push_back(*p_index);
            p_index++;
        }
        if (*p_index != '=')
        {
            std::stringstream ss;
            ss << "Token:" << token << "  option:" << _option_name << " ??";
            throw std::runtime_error(ss.str().c_str());
        }
        p_index++;
        while (*p_index == ' ' && *p_index != '>' && p_index < p_end)p_index++;
        if (*p_index != '"')
        {
            std::stringstream ss;
            ss << "Token:" << token << "  option:" << _option_name << " = missing \"";
            throw std::runtime_error(ss.str().c_str());
        }
        p_index++;
        while (*p_index != '"' && *p_index != '>' && p_index < p_end)
        {
            if (*p_index > ' ') _option_value.push_back(*p_index);
            p_index++;
        }
        p_index++;
        optl.insert(optionPair(_option_name,_option_value));
    }
}

bool miniXmlParse::captureToken(std::string &token,
                                optionsList & optl,
                                bool &skipvalue)
{
    skipvalue=false;
    optl.clear();
    while (*p_index != '>' && p_index < p_end)
    {
        if(*p_index<=' ')
        {
            captureOption(token, optl);
            if(*p_index=='/')
            {
                p_index++;
                if (*p_index == '>')skipvalue = true;
            }
            break;
        }
        else if(*p_index=='/')
        {
            p_index++;
            if(*p_index== '>')skipvalue=true;
        }
        else
        {
            token.push_back(*p_index);
            p_index++;
        }
    }
    p_index++;
    return isEnd();
}


bool miniXmlParse::captureToken(std::string &token)
{
    while (*p_index != '>' && p_index < p_end)
    {
        if(*p_index<=' ')
        {
            while (*p_index == ' ' && *p_index != '>' && p_index < p_end)p_index++;
            if (*p_index != '>')
            {
                std::stringstream ss;
                ss<<"Bad xml format missing >"<<std::endl;
                throw std::runtime_error(ss.str().c_str());
            }
        }
        else
        {
            token.push_back(*p_index);
            p_index++;
        }
    }
    p_index++;
    return isEnd();
}

bool miniXmlParse::captureValue(std::string &token)
{
    //skip initial space
    while (*p_index==' ' && *p_index != '<' && p_index < p_end)p_index++;
    while (*p_index != '<' && p_index < p_end)
    {
        if (*p_index >= ' ')
            token.push_back(*p_index);
        p_index++;
    }
    return isEnd();
}

bool miniXmlParse::skipSpaces(bool space)
{

    typedef struct test_space
    {
        static bool check(_cbt p,bool space)
        {
            int v = (int) p;
            if(space)
            {
                return ( (v <=(int) (' ')) ||
                         (v == (int)(0xfffe)) );
            }
            else
            {
                return ((v < (int) (' ')) ||
                        (v == (int) (0xfffe)));
            }
        }
    } space_tester;

    while (space_tester::check(*p_index,space) && p_index < p_end)
        p_index++;
    return isEnd();
}

bool miniXmlParse::parse()
{
    auto res=false;
    if (!filebuff.empty() && root != nullptr)
    {
        miniXmlNode *current = root;
        if (p_index != p_end)
        {
            if (*p_index != '<')
            {
#ifdef _UNICODE
                _cbt p = *p_index;
                if (p == 0xfffe)
                {
                    //TODO TEST on mbt
                    std::runtime_error e("bad multi byte file format");
                    throw e;
                }
                else if (p == 0xfeff)
                {
                    p_index++;
                    p_index++;
                }
            }
#else
                p_index++;
                if (*p_index != '<')
                {
                    //bad format of xml

                    throw std::runtime_error("Xml bad format error : missing <");
                }
#endif
        }
        bool first = false;
        res = getTokens(&current, &first);
        if(p_index!=p_end)
        {
            std::string msg;
            while(p_last<p_index)
            {
                msg += *p_last;
                p_last++;
            }
            std::stringstream ss;
            ss<<"Parse error at index : "<<(size_t)(p_index-p_start)<<
              " '"<<msg<<"' "<<std::endl;
            throw std::runtime_error ( ss.str().c_str());
        }
    }
}
return res;
}



}