//
// Created by angelo on 08/06/19.
//

#ifndef QXMLC_CAARGOPT_H
#define QXMLC_CAARGOPT_H


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
#include <set>


namespace CA
{


class optionArgvBase
    : public CA::IOptionArgv
{
protected:
    std::string optionName;
    optionArgvType type;
    bool status;
    helpFunctor help;
    size_t offset;
public:
    ~optionArgvBase() override
    {
        status = false;
        type = optARGV_NONE;
        optionName.clear();
    }

    optionArgvBase(size_t _offset,const _cbt *_name,helpFunctor _help)
        : offset(_offset),optionName(_name),  help(_help)
    {
        status = false;
        type = optARGV_NONE;
    }

    inline const _cbt *getName() final
    {
        return optionName.c_str();
    };

    inline const helpFunctor getHelpFunctor() final
    {
        return help;
    };
    inline bool isSelect() final
    {
        return status;
    }
    inline size_t getIntValue() override
    {
        return 0;
    };
    inline  size_t getOffset() final
    {
        return offset;
    };
};

class optionArgvBoolParser
    : public CA::optionArgvBase
{
public :
    optionArgvBoolParser( size_t _offset, const _cbt *_name,
                          helpFunctor _help = nullptr)
        : optionArgvBase( _offset, _name, _help)
    {
        type = optARGV_BOOL;
    }

    bool parse(const char *argv[], size_t size, size_t &index) final;

    const _cbt *  getStringValue() final;
};

class optionArgvStringParser
    : public CA::optionArgvBase
{
    std::string inputS;
public :
    optionArgvStringParser(size_t _offset, const _cbt *_name,
                           helpFunctor _help = nullptr)
        : optionArgvBase( _offset, _name, _help )
    {
        inputS="";
        type = optARGV_STRING;
    }

    bool parse(const char *argv[], size_t size, size_t &index) final;

    const _cbt * getStringValue() final;
};

class optionArgvIntParser
    : public CA::optionArgvBase
{
    size_t min_value;
    size_t max_value;
    size_t inputI;
public :
    optionArgvIntParser(size_t _offset,
                        const _cbt *_name,
                        size_t _default_value = 0,
                        size_t _min_value = 0,
                        size_t _max_value = SIZE_MAX,
                        helpFunctor _help = nullptr)
        : optionArgvBase( _offset, _name, _help)
    {
        type = optARGV_INT;
        min_value = _min_value;
        max_value = _max_value;
        inputI=_default_value;
    }

    bool parse(const char *argv[], size_t size, size_t &index) final;

    const _cbt * getStringValue() final;

    inline size_t getIntValue()   final
    {
        return inputI;
    }
};
}

#endif //QXMLC_CAARGOPT_H
