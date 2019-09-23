#ifndef QXMLC_CACONFENV_H
#define QXMLC_CACONFENV_H


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

class  caGetConfEnv
    :public IGetConfEnv
{
protected:
    envMap keyVal;
    void replaceValue(std::string & in, std::string & out);
public:
    caGetConfEnv(const char *home,const char *pwd,const char *user);
    explicit caGetConfEnv(  IGetConfEnv * b);
    ~caGetConfEnv() final;
    bool add(const char *key,std::string value) final;
    bool add(envMap & map)final ;
    bool getValue(const char * key ,std::string & out ) final;
    void dump(const char *envname) final;
    void append( IGetConfEnv * root) final;
    inline envMap & getMap() final { return keyVal;}
    void addEnvToScript(std::ofstream & of) final;
};
}




#endif
