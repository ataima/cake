#ifndef CA_UTILS_HEADER
#define CA_UTILS_HEADER


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


namespace CA
{

class caUtils
{
    /* bool function return true for OK result */
public:
    static bool checkDirExistOrCreate(std::string & dir);
    static bool checkDirExist(std::string & dir);
    static void appendPath(std::string & root,std::string & path);
    static bool checkFileExist(std::string & file);
    static bool compareFileChangeDate(std::string & root, std::string & child);
    static bool compareDirChangeDate(std::string & root, std::string & child);
    static bool removeDir(std::string & path);
    static bool baseName(std::string & path, std::string & filename);
    static bool baseNameNoExt(std::string & path, std::string & filename);
    static bool dirName(std::string & path, std::string & dirname);
    static bool baseExt(std::string & file, std::string & ext);

};

}

#endif