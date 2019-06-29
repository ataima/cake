#ifndef CA_MAIN_APP_FILE_HEADER
#define CA_MAIN_APP_FILE_HEADER


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

typedef enum tag_flg_index
{
    f_help,
    f_verbose,
    f_debug,
    f_last_flags
} availOption;



class mainAppExecutor
    :public CA::IMainAppExecutor
{
    static void Help(IOptionArgvManager *manager);
    static void Help_verbose(IOptionArgvManager *manager);
    static void Help_debug(IOptionArgvManager * manager );
public:
    mainAppExecutor() ;
    ~mainAppExecutor() final;
    bool init(const char * argv[],size_t size)final;
    bool execute() final;
};

}
#endif //CA_MAIN_APP_FILE_HEADER
