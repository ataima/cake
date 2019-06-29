#ifndef CA_ARGV_FILE_HEADER
#define CA_ARGV_FILE_HEADER


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

#include "cainterfaces.h"

namespace CA
{


class argvManager
    :public CA::IOptionArgvManager
{
protected:
    optionMap options;
    optionDir optionsDir;
    stringList args;
private:
    static void replaceRelative(stringList & ls,const char *abspath);
    void prepareInput();
public:
    explicit argvManager( size_t reqOptionNum);
    ~argvManager() final;
    void Parse(const char * argv[],size_t size) final;
    bool saveAsXml(const _cbt * filename) final;
    void addOption(IOptionArgv *reqOpt) final;
    inline  const optionMap & getOptionsMap() final
    {
        return options;
    }
    inline  const optionDir & getOptionsArray() final
    {
        return optionsDir;
    }
    IOptionArgv & getOption(const std::string & opt) final;
    IOptionArgv & getOption(size_t offset) final ;
    inline const stringList & getArgs() final
    {
        return args;
    }
    static inline void InitManager(size_t _max_option)
    {
        new argvManager( _max_option );
    }
};


}

#endif //CA_ARGV_FILE_HEADER
