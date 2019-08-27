#include <cacakemanager.h>
#include "caminiXml.h"
#include "calogiface.h"
#include "calogger.h"
#include "caargopt.h"
#include "caargv.h"
#include "camain.h"


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

mainAppExecutor::mainAppExecutor()
{
    auto logger=new CA::Logger();
    logger->addOutput(new CA::DefaultPrinter());
}

mainAppExecutor::~mainAppExecutor()
{
    delete CA::ILogger::getInstance();
}

bool mainAppExecutor::init(const char *argv[], size_t size)
{
    argvManager::InitManager(f_last_flags);
    IOptionArgvManager *argvObj=IOptionArgvManager::getInstance();
    if (argvObj)
    {
        argvObj->addOption(new
                           optionArgvBoolParser(f_help,"--help",mainAppExecutor::Help));
        argvObj->addOption(new
                           optionArgvIntParser(f_verbose,"--verbose",5,0,7,mainAppExecutor::Help_verbose));
        argvObj->addOption(new
                           optionArgvBoolParser(f_debug,"--debug",mainAppExecutor::Help_debug));
        if(size==1)
        {
            argvObj->getOption(f_help).getHelpFunctor()(argvObj);
            exit(0);
        }
        try
        {
            argvObj->Parse(argv, size);
        }
        catch (std::runtime_error & e)
        {
            // trow exception with --help in input pass exception...
            if(!argvObj->getOption(f_help).isSelect())
                throw e;
        }
        // manage --verbose level
        if(ILogger::getInstance()!=nullptr)
            ILogger::getInstance()->setLogLevel(argvObj->getOption(f_verbose).getIntValue());
        // managin help
        if(argvObj->getOption(f_help).isSelect())
        {
            if(argvObj->getOption(f_verbose).isSelect())
            {
                argvObj->getOption(f_verbose).getHelpFunctor()(argvObj);
            }
            else if(argvObj->getOption(f_debug).isSelect())
            {
                argvObj->getOption(f_debug).getHelpFunctor()(argvObj);
            }
            else
                argvObj->getOption(f_help).getHelpFunctor()(argvObj);
            exit(0);
        }
    }
    return true;
}


bool mainAppExecutor::execute()
{
    auto res=false;
    IOptionArgvManager *argvObj=IOptionArgvManager::getInstance();
    if( ! argvObj->getArgs().empty())
    {
        for  ( const std::string & it : argvObj->getArgs())
        {
            cakeManager manager;
            LogInfo("Starting %sCAKE%s : %s ", RED_LIGHT, WHITE,it.c_str());
            if(manager.run(it))
            {
                manager.reset();
            }
        }
    }
    else
    {
        LogError("Missing input xml file.... stop!");
    }

    return res;
}


void mainAppExecutor::Help(IOptionArgvManager *manager )
{
    std::cout<<GREEN_LIGHT<<"Available commands :"<<REPLACE<<std::endl;
    for(const std::pair<const std::string ,CA::IOptionArgv *> & it : manager->getOptionsMap() )
    {
        std::cout<<it.first<<std::endl;
    }
    std::cout<<YELLOW<<"use --help  <command> to obtain more help"<<REPLACE<<std::endl;
    exit(0);
}




void mainAppExecutor::Help_verbose(IOptionArgvManager * /* manager */ )
{
    std::cout<<GREEN_LIGHT<<"--verbose <0..7>"<<REPLACE<<std::endl;
    std::cout<<"this option enable verbosity : 0 off 7 max verbosity"<<std::endl;
    std::cout<<"default verbosity = 6"<<REPLACE<<std::endl;
    exit(0);
}



void mainAppExecutor::Help_debug(IOptionArgvManager * /* manager */ )
{
    std::cout<<GREEN_LIGHT<<"--debug "<<REPLACE<<std::endl;
    std::cout<<"If insert this option, qxmlc create a file <>.xml.debug "<<std::endl;
    std::cout<<"this is a work file to generate code e xslt"<<REPLACE<<std::endl;
    exit(0);
}

}
