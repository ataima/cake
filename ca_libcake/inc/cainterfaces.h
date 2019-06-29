#ifndef CA_INTERFACES
#define CA_INTERFACES

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



#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <thread>
#include <set>
#include <fstream>
#include <string>

#ifndef _MSC_VER
#pragma pack(0)
#endif
//////////////////////////////////////////////////////


namespace CA
{


#define  BUFFLENGTH  512

#ifdef _DOUBLE_UNICODE
typedef  char32_t     _cbt;
#else
#ifdef _UNICODE
typedef  char16_t     _cbt;
#else
typedef  char     _cbt;
#endif
#endif



class IOptionArgvManager;

typedef void (*helpFunctor)(IOptionArgvManager *manager);


class IOptionArgv
{
public:
    typedef enum tag_ioption_argv
    {
        optARGV_NONE,
        optARGV_BOOL,
        optARGV_STRING,
        optARGV_INT
    } optionArgvType;
public:
    virtual ~IOptionArgv()=default;
    virtual const _cbt * getName()=0;
    virtual bool parse(const char * argv[],size_t size,size_t & index)=0;
    virtual const _cbt * getStringValue()=0;
    virtual size_t getIntValue()=0;
    virtual bool  isSelect()=0;
    virtual const helpFunctor getHelpFunctor()=0;
    virtual size_t getOffset()=0;
    static  bool  isOption(const _cbt *arg);
};





typedef std::list<std::string> stringList;
typedef std::map<const std::string ,CA::IOptionArgv *> optionMap;
typedef std::vector<CA::IOptionArgv *> optionDir;

class IOptionArgvManager
{
protected:
    static IOptionArgvManager *instance;
public:
    virtual ~IOptionArgvManager()
    {
        instance =nullptr;
    }
    virtual void Parse(const char * argv[],size_t size)=0;
    virtual bool saveAsXml(const _cbt * filename)=0;
    static IOptionArgvManager * getInstance()
    {
        return instance;
    }
    static bool checkOption(size_t offset)
    {
        if(instance)
        {
            return instance->getOptionsArray().at(offset)->isSelect();
        }
        return false;
    }
    virtual void addOption(IOptionArgv * reqOpt)=0;
    virtual const optionMap & getOptionsMap()=0;
    virtual const optionDir & getOptionsArray()=0;
    virtual const stringList & getArgs()=0;
    virtual IOptionArgv & getOption(size_t)=0;
    virtual IOptionArgv & getOption(const std::string & opt)=0;
};



class ICake
{
public:
    virtual bool run(const std::string & conf_file)=0;
    virtual bool reset()=0;
};



class IMainAppExecutor
{
public:
    virtual ~IMainAppExecutor()=default;
    virtual bool init(const char * argv[],size_t size)=0;
    virtual bool execute()=0;
};

}

#endif // CAINTERFACES

