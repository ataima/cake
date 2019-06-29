#include "caminiXml.h"
#include "calogiface.h"
#include "calcfxml.h"


#define DEBUG_NODE_TYPE 0
#define DEBUG_TOSTRING 0





static const char * dbgaid[]=
{
    "inode_simple",
    "inode_simple_with_options",
    "inode_childs",
    "inode_childs_with_options",
    "inode_array",
    "inode_array_with_options",
    "inode_array_childs",
    "inode_array_childs_with_options"
};



void  LCFXml::setError(CA::IXmlNode *node,std::string what,std::string &name,std::string & fullname)
{

    std::stringstream error;
    std::stringstream  parent;
    if(node!=nullptr)
    {
        parent << node->getName();
        CA::IXmlNode::xmlNodeType type=node->getNodeType();
        if(type==CA::IXmlNode::xmlNodeType::inode_array ||
                type==CA::IXmlNode::xmlNodeType::inode_array_with_options||
                type==CA::IXmlNode::xmlNodeType::inode_array_childs ||
                type==CA::IXmlNode::xmlNodeType::inode_array_childs_with_options)
        {
            parent<<"["<<node->getIndex()<<"]";
        }
        if(!node->getOptions().empty())
        {
            std::stringstream vv;
            for(auto & it:node->getOptions())
            {
                vv.str("");
                vv<<it.first<<"\""<<it.second<<"\"";
                parent<<vv.str()<<" ";
            }
        }
    }
    error << RED_LIGHT<<"Error"<<REPLACE<<": "<<GREEN_LIGHT<< "on xml node ' "<<
          parent.str()<<" ' "<<REPLACE<<" : "<<BLUE<<what << REPLACE<<" : "<<
          YELLOW << name << REPLACE<<" ( "<<PURPLE<<fullname<< REPLACE<<" )"<<
          std::endl;
    throw std::runtime_error(error.str().c_str());
}


void  LCFXml::setWarning(CA::IXmlNode *node,std::string  what,std::string &name,std::string & fullname)
{

    std::stringstream error;
    std::stringstream  parent;
    if(node!=nullptr)
    {
        parent << node->getName();
        CA::IXmlNode::xmlNodeType type=node->getNodeType();
        if(type==CA::IXmlNode::xmlNodeType::inode_array ||
                type==CA::IXmlNode::xmlNodeType::inode_array_with_options||
                type==CA::IXmlNode::xmlNodeType::inode_array_childs ||
                type==CA::IXmlNode::xmlNodeType::inode_array_childs_with_options)
        {
            parent<<"["<<node->getIndex()<<"]";
        }
        if(!node->getOptions().empty())
        {
            auto it=node->getOptions().begin();
            auto stop=node->getOptions().end();
            parent<<" with (";
            std::stringstream vv;
            for(auto & vit : node->getOptions())
            {
                vv.str("");
                vv<<vit.first<<"\"="<<vit.second<<"\"";
                parent<<vv.str()<<" ";
            }
            parent<<")";
        }
    }
    error << GREEN<<"Warning "<<REPLACE<<": "<<BLUE<< "on xml node ' "<<parent.str()<<
          " '"<<REPLACE" : "<<BROWN<<what <<REPLACE<< " : "<<GRAY_DARK<< name <<REPLACE<<
          " ( "<<PURPLE<<fullname<< REPLACE<<")"<< std::endl;
    std::cerr<<error.str();
}



bool  LCFXml::checkOptions(CA::IXmlNode::xmlNodeType one , CA::IXmlNode::xmlNodeType two)
{
    switch(one)
    {
    case CA::IXmlNode::xmlNodeType::inode_simple:
        if (two==CA::IXmlNode::xmlNodeType::inode_simple_with_options)
        {
            return false;
        }
        else   if (two==CA::IXmlNode::xmlNodeType::inode_array)
        {
            return false;
        }
        else   if (two==CA::IXmlNode::xmlNodeType::inode_array_with_options)
        {
            return false;
        }
        break;
    case CA::IXmlNode::xmlNodeType::inode_simple_with_options:
        if (two==CA::IXmlNode::xmlNodeType::inode_simple)
        {
            return false;
        }
        else if (two==CA::IXmlNode::xmlNodeType::inode_array)
        {
            return false;
        }
        else if (two==CA::IXmlNode::xmlNodeType::inode_array_with_options)
        {
            return false;
        }
    case CA::IXmlNode::xmlNodeType::inode_childs:
        if (two==CA::IXmlNode::xmlNodeType::inode_childs_with_options)
        {
            return false;
        }
        else if (two==CA::IXmlNode::xmlNodeType::inode_array_childs)
        {
            return false;
        }
        else if (two==CA::IXmlNode::xmlNodeType::inode_array_childs_with_options)
        {
            return false;
        }
        break;
    case CA::IXmlNode::xmlNodeType::inode_childs_with_options:
        if (two==CA::IXmlNode::xmlNodeType::inode_childs)
        {
            return false;
        }
        else if (two==CA::IXmlNode::xmlNodeType::inode_array_childs)
        {
            return false;
        }
        else if (two==CA::IXmlNode::xmlNodeType::inode_array_childs_with_options)
        {
            return false;
        }
        break;
    case CA::IXmlNode::xmlNodeType::inode_array:
        if (two==CA::IXmlNode::xmlNodeType::inode_array_with_options)
        {
            return false;
        }
        else if (two==CA::IXmlNode::xmlNodeType::inode_simple)
        {
            return false;
        }
        else if (two==CA::IXmlNode::xmlNodeType::inode_simple_with_options)
        {
            return false;
        }
        break;
    case CA::IXmlNode::xmlNodeType::inode_array_with_options:
        if (two==CA::IXmlNode::xmlNodeType::inode_array)
        {
            return false;
        }
        else if (two==CA::IXmlNode::xmlNodeType::inode_simple)
        {
            return false;
        }
        else if (two==CA::IXmlNode::xmlNodeType::inode_simple_with_options)
        {
            return false;
        }
    case CA::IXmlNode::xmlNodeType::inode_array_childs:
        if (two==CA::IXmlNode::xmlNodeType::inode_array_childs_with_options)
        {
            return false;
        }
        break;
    case CA::IXmlNode::xmlNodeType::inode_array_childs_with_options:
        if (two==CA::IXmlNode::xmlNodeType::inode_array_childs)
        {
            return false;
        }
        break;
    }
    return true;
}

void  LCFXml::copyOptions(CA::optionsList * src,CA::optionsList * dest)
{
    if( src==nullptr || dest==nullptr) return;
    if(!src->empty())
    {
        dest->clear();
        for (auto & it  : *src)
        {
            CA::optionPair nv(it.first,it.second);
            dest->insert(nv);
        }
    }
}

void  LCFXml::loadFromXml(CA::IXmlNode *node,IKeyValue *obj)
{
    keyList *list=obj->getICAXml_Predef_List();
    for(auto it : *list )
    {
#if  DEBUG_NODE_TYPE
        std::cout<<it->type<<"   - "<<dbgaid[it->type]<<" :: "<<it->fullname<<std::endl;
#endif
        switch(it.type)
        {
        case CA::IXmlNode::xmlNodeType::inode_simple:
        {
            CA::IXmlNode *v = node->find(it.name);
            if ( v != nullptr )
            {
                if (it.type!=v->getNodeType())
                {
                    if (checkOptions(it.type, v->getNodeType()))
                    {
                        std::stringstream ss;
                        ss << "Incompatible node type\n " << dbgaid[it.type] << " <-> "
                           << dbgaid[v->getNodeType()];
                        setError(node,ss.str(),it.name, it.fullname);
                    }
                    else
                    {
                        std::stringstream ss;
                        unsigned int mt,Mt;
                        if (it.type<v->getNodeType())
                        {
                            mt=it.type;
                            Mt=v->getNodeType();
                        }
                        else
                        {
                            Mt=it.type;
                            mt=v->getNodeType();
                        }
                        ss << "\npromote from " << dbgaid[mt] << " to "
                           << dbgaid[Mt];
                        setWarning(node, ss.str(), it.name, it.fullname);
                    }
                }
                *it.D.S.simple=v->getValue();
            }
            else
            {
                setWarning(node,"missing child node ",it.name,it.fullname);
            }
        }
        break;
        case CA::IXmlNode::xmlNodeType::inode_simple_with_options:
        {
            CA::IXmlNode *v = node->find(it.name);
            if (v != nullptr )
            {
                if (it.type!=v->getNodeType())
                {
                    if (checkOptions(it.type, v->getNodeType()))
                    {
                        std::stringstream ss;
                        ss << "Incompatible node type\n " << dbgaid[it.type] << " <-> "
                           << dbgaid[v->getNodeType()];
                        setError(node,ss.str(),it.name, it.fullname);
                    }
                    else
                    {
                        std::stringstream ss;
                        unsigned int mt,Mt;
                        if (it.type<v->getNodeType())
                        {
                            mt=it.type;
                            Mt=v->getNodeType();
                        }
                        else
                        {
                            Mt=it.type;
                            mt=v->getNodeType();
                        }
                        ss << "\npromote from " << dbgaid[mt] << " to "
                           << dbgaid[Mt];
                        setWarning(node, ss.str(), it.name, it.fullname);
                    }
                }
                *it.D.O.simple=v->getValue();
                LCFXml::copyOptions(&v->getOptions(),it.D.O.options);
            }
            else
            {
                setWarning(node,"missing child node ",it.name,it.fullname);
            }
        }
        break;
        case CA::IXmlNode::xmlNodeType::inode_childs:
        {
            CA::IXmlNode *v = node->find(it.name);
            if ( v != nullptr )
            {
                if (it.type!=v->getNodeType())
                {
                    if (checkOptions(it.type, v->getNodeType()))
                    {
                        std::stringstream ss;
                        ss << "Incompatible node type\n " << dbgaid[it.type] << " <-> "
                           << dbgaid[v->getNodeType()];
                        setError(node,ss.str(),it.name, it.fullname);
                    }
                    else
                    {
                        std::stringstream ss;
                        unsigned int mt,Mt;
                        if (it.type<v->getNodeType())
                        {
                            mt=it.type;
                            Mt=v->getNodeType();
                        }
                        else
                        {
                            Mt=it.type;
                            mt=v->getNodeType();
                        }
                        ss << "\npromote from " << dbgaid[mt] << " to "
                           << dbgaid[Mt];
                        setWarning(node, ss.str(), it.name, it.fullname);
                    }
                }
                *it.D.C.value=v->getValue();
                it.D.C.childs->loadFromXml(v);
            }
            else
            {
                setWarning(node,"missing child node ",it.name,it.fullname);
            }
        }
        break;
        case CA::IXmlNode::xmlNodeType::inode_childs_with_options:
        {
            CA::IXmlNode *v = node->find(it.name);
            if (v != nullptr )
            {
                if (it.type!=v->getNodeType())
                {
                    if (checkOptions(it.type, v->getNodeType()))
                    {
                        std::stringstream ss;
                        ss << "Incompatible node type\n " << dbgaid[it.type] << " <-> "
                           << dbgaid[v->getNodeType()];
                        setError(node,ss.str(),it.name, it.fullname);
                    }
                    else
                    {
                        std::stringstream ss;
                        unsigned int mt,Mt;
                        if (it.type<v->getNodeType())
                        {
                            mt=it.type;
                            Mt=v->getNodeType();
                        }
                        else
                        {
                            Mt=it.type;
                            mt=v->getNodeType();
                        }
                        ss << "\npromote from " << dbgaid[mt] << " to "
                           << dbgaid[Mt];
                        setWarning(node, ss.str(), it.name, it.fullname);
                    }
                }
                *it.D.F.value=v->getValue();
                LCFXml::copyOptions(&v->getOptions(),it.D.F.options);
                it.D.F.childs->loadFromXml(v);
            }
            else
            {
                setWarning(node,"missing child node ",it.name,it.fullname);
            }
        }
        break;
        case CA::IXmlNode::xmlNodeType::inode_array:
        {
            std::vector<std::string > *nout=it.D.N.array;
            std::vector<CA::IXmlNode *> result;
            node->getChildNameList(it.name,&result,nullptr);
            if(!result.empty())
            {
                for ( auto uit : result)
                {
                    CA::IXmlNode *v=uit;
                    if (v != nullptr )
                    {
                        if (it.type!=v->getNodeType())
                        {
                            if (checkOptions(it.type, v->getNodeType()))
                            {
                                std::stringstream ss;
                                ss << "Incompatible node type\n " << dbgaid[it.type] << " <-> "
                                   << dbgaid[v->getNodeType()];
                                setError(node,ss.str(),it.name, it.fullname);
                            }
                            else
                            {
                                std::stringstream ss;
                                unsigned int mt,Mt;
                                if (it.type<v->getNodeType())
                                {
                                    mt=it.type;
                                    Mt=v->getNodeType();
                                }
                                else
                                {
                                    Mt=it.type;
                                    mt=v->getNodeType();
                                }
                                ss << "\npromote from " << dbgaid[mt] << " to "
                                   << dbgaid[Mt];
                                setWarning(node, ss.str(), it.name, it.fullname);
                            }
                        }
                        nout->push_back(v->getValue());
                    }
                    else
                    {
                        setWarning(node,"missing child node ",it.name,it.fullname);
                    }
                    uit++;
                }
            }
            else
            {
                setWarning(node,"missing child node ",it.name,it.fullname);
            }
        }
        break;
        case CA::IXmlNode::xmlNodeType::inode_array_with_options:
        {
            std::vector <CA::pairValue> *n1out=it.D.W.array;
            std::vector<CA::IXmlNode *> result;
            node->getChildNameList(it.name,&result,nullptr);
            if(!result.empty())
            {
                for( auto uit : result )
                {
                    CA::IXmlNode *v=uit;
                    if (v != nullptr )
                    {
                        if (it.type!=v->getNodeType())
                        {
                            if (checkOptions(it.type, v->getNodeType()))
                            {
                                std::stringstream ss;
                                ss << "Incompatible node type\n " << dbgaid[it.type] << " <-> "
                                   << dbgaid[v->getNodeType()];
                                setError(node,ss.str(),it.name, it.fullname);
                            }
                            else
                            {
                                std::stringstream ss;
                                unsigned int mt,Mt;
                                if (it.type<v->getNodeType())
                                {
                                    mt=it.type;
                                    Mt=v->getNodeType();
                                }
                                else
                                {
                                    Mt=it.type;
                                    mt=v->getNodeType();
                                }
                                ss << "\npromote from " << dbgaid[mt] << " to "
                                   << dbgaid[Mt];
                                setWarning(node, ss.str(), it.name, it.fullname);
                            }
                        }
                        CA::pairValue p;
                        p.first=v->getValue();
                        LCFXml::copyOptions(&v->getOptions(),&p.second);
                        n1out->push_back(p);
                    }
                    else
                    {
                        setWarning(node,"missing child node ",it.name,it.fullname);
                    }
                    uit++;
                }
            }
            else
            {
                setWarning(node,"missing child node ",it.name,it.fullname);
            }
        }
        break;
        case CA::IXmlNode::xmlNodeType::inode_array_childs:
        {
            std::vector<IClonable * > *n2out=it.D.A.childs_array;
            IClonable *_base=it.D.A.obj;
            std::vector<CA::IXmlNode *> result;
            node->getChildNameList(it.name,&result,nullptr);
            if(!result.empty())
            {
                for (auto uit : result )
                {
                    CA::IXmlNode *v=uit;
                    if (v != nullptr )
                    {
                        if (it.type!=v->getNodeType())
                        {
                            if (checkOptions(it.type, v->getNodeType()))
                            {
                                std::stringstream ss;
                                ss << "Incompatible node type\n " << dbgaid[it.type] << " <-> "
                                   << dbgaid[v->getNodeType()];
                                setError(node,ss.str(),it.name, it.fullname);
                            }
                            else
                            {
                                std::stringstream ss;
                                unsigned int mt,Mt;
                                if (it.type<v->getNodeType())
                                {
                                    mt=it.type;
                                    Mt=v->getNodeType();
                                }
                                else
                                {
                                    Mt=it.type;
                                    mt=v->getNodeType();
                                }
                                ss << "\npromote from " << dbgaid[mt] << " to "
                                   << dbgaid[Mt];
                                setWarning(node, ss.str(), it.name, it.fullname);
                            }
                        }
                        IClonable *clone=_base->clone();
                        clone->loadFromXml(v);
                        clone->setInternalValue(v->getValue());
                        n2out->push_back(clone);
                    }
                    else
                    {
                        setWarning(node,"missing child node ",it.name,it.fullname);
                    }
                    uit++;
                }
            }
            else
            {
                setWarning(node,"missing child node ",it.name,it.fullname);
            }
        }

        break;
        case CA::IXmlNode::xmlNodeType::inode_array_childs_with_options:
        {
            std::vector<IClonableOption * > *n3out=it.D.Z.childs_array;
            IClonableOption *_base=it.D.Z.obj;
            std::vector<CA::IXmlNode *> result;
            node->getChildNameList(it.name,&result,nullptr);
            if(!result.empty())
            {
                for (auto uit :  result)
                {
                    CA::IXmlNode *v=uit;
                    if (v != nullptr )
                    {
                        if (it.type!=v->getNodeType())
                        {
                            if (checkOptions(it.type, v->getNodeType()))
                            {
                                std::stringstream ss;
                                ss << "Incompatible node type\n " << dbgaid[it.type] << " <-> "
                                   << dbgaid[v->getNodeType()];
                                setError(node,ss.str(),it.name, it.fullname);
                            }
                            else
                            {
                                std::stringstream ss;
                                unsigned int mt,Mt;
                                if (it.type<v->getNodeType())
                                {
                                    mt=it.type;
                                    Mt=v->getNodeType();
                                }
                                else
                                {
                                    Mt=it.type;
                                    mt=v->getNodeType();
                                }
                                ss << "\npromote from " << dbgaid[mt] << " to "
                                   << dbgaid[Mt];
                                setWarning(node, ss.str(), it.name, it.fullname);
                            }
                        }
                        auto *clone=dynamic_cast<IClonableOption*>(_base->clone());
                        clone->loadFromXml(v);
                        clone->setInternalValue(v->getValue());
                        clone->setOptionList(v->getOptions());
                        n3out->push_back(clone);
                    }
                    else
                    {
                        setWarning(node,"missing child node ",it.name,it.fullname);
                    }
                    uit++;
                }
            }
            else
            {
                setWarning(node,"missing child node ",it.name,it.fullname);
            }
        }
        break;
        default:
        {
            setError(node,"Unknow node type on object",it.name,it.fullname);
        }
        }
    }
}


void  LCFXml::toString(std::iostream &ss,CA::optionsList * optl)
{
    if(optl!=nullptr && !optl->empty())
    {
        ss << " ";
        for (auto & it : *optl )
        {
            ss << it.first << "=\"" << it.second << "\" ";
        }
    }
}

void  LCFXml::toString(std::iostream &out,IKeyValue *obj,std::string & parent)
{
    keyList *list=obj->getICAXml_Predef_List();
    std::stringstream ss;
    std::string tab;
    for(auto it : *list)
    {
        ss.str("");
        switch(it.type)
        {
        case CA::IXmlNode::xmlNodeType::inode_simple:
            if(!it.D.S.simple->empty())
            {
                ss << parent << "<" << it.name << ">" << *(it.D.S.simple) <<
                   "</" << it.name << ">" << std::endl;
            }
            else
            {
                ss << parent << "<" << it.name << "/>"<< std::endl;
            }
            break;
        case CA::IXmlNode::xmlNodeType::inode_simple_with_options:
            ss<<parent<<"<"<<it.name;
            toString(ss,it.D.O.options);
            if(!it.D.O.simple->empty())
            {
                ss << ">" << *(it.D.O.simple) <<
                   "</" << it.name << ">" << std::endl;
            }
            else
            {
                ss << "/>"<< std::endl;
            }
            break;
        case CA::IXmlNode::xmlNodeType::inode_childs:
            ss << parent << "<" << it.name << ">" << *(it.D.C.value) << std::endl;
            tab= parent + "    ";
            LCFXml::toString(ss, it.D.C.childs, tab);
            ss << parent << "</" << it.name << ">" << std::endl;
            break;
        case CA::IXmlNode::xmlNodeType::inode_childs_with_options:
            ss<<parent<<"<"<<it.name;
            toString(ss,it.D.F.options);
            ss<<">"<<*(it.D.F.value)<<std::endl;
            tab= parent + "    ";
            LCFXml::toString(ss,it.D.F.childs,tab);
            ss<<parent<<"</"<<it.name<<">"<<std::endl;
            break;
        case CA::IXmlNode::xmlNodeType::inode_array:
        {
            std::vector<std::string > *lout=it.D.N.array;
            auto num=0;
            for(auto & uit : *lout)
            {
                if(!uit.empty())
                {
                    ss << parent << "<" << it.name << ">" << uit <<
                       "</" << it.name << ">" << std::endl;
                }
                else
                {
                    ss << parent << "<" << it.name << "/>" << std::endl;
                }
                num++;
            }
        }
        break;
        case CA::IXmlNode::xmlNodeType::inode_array_with_options:
        {
            std::vector<CA::pairValue > *l1out=it.D.W.array;
            auto num=0;
            for(auto uit : *l1out)
            {
                if(!uit.first.empty())
                {
                    ss << parent << "<" << it.name;
                    toString(ss, &uit.second);
                    ss << ">" << uit.first <<
                       std::endl << parent << "</" << it.name << ">" << std::endl;
                }
                else
                {
                    ss << parent << "<" << it.name;
                    toString(ss, &uit.second);
                    ss << "/>" << std::endl;
                }
                num++;
            }
        }
        break;
        case CA::IXmlNode::xmlNodeType::inode_array_childs:
        {
            std::vector<IClonable *> *l2out=it.D.A.childs_array;
            auto num=0;
            for (auto uit : *l2out)
            {
                ss<<parent<<"<"<<it.name<<">"<<(*uit).getInternalValue()<<std::endl;
                tab= parent + "    ";
                LCFXml::toString(ss,uit,tab);
                ss<<parent<<"</"<<it.name<<">"<<std::endl;
                num++;
                uit++;
            }
        }
        break;
        case CA::IXmlNode::xmlNodeType::inode_array_childs_with_options:
        {
            std::vector<IClonableOption *> *l3out=it.D.Z.childs_array;
            auto num=0;
            for (auto uit : *l3out)
            {

                ss<<parent<<"<"<<it.name;
                toString(ss,&(*uit).getOptionsList());
                ss<<">"<<(*uit).getInternalValue()<<std::endl;
                tab= parent + "    ";
                LCFXml::toString(ss,uit,tab);
                ss<<parent<<"</"<<it.name<<">"<<std::endl;
                num++;
                uit++;
            }
        }
        break;
        default:
        {
            setError(nullptr,"Unknow node type on object",it.name,it.fullname);
        }
        }
#if DEBUG_TOSTRING
        std::cout<<out.str();
#endif
        out<<ss.str();
    }
}


void LCFXml::deleteChildsArray( std::vector<IClonable *> *objs)
{

    for ( auto it : *objs)
    {
        delete it;
    }
    objs->clear();
}


void LCFXml::deleteChildsArray(std::vector<IClonableOption *> *objs)
{
    for ( auto it : *objs)
    {
        delete it;
    }
    objs->clear();
}
