#include "stdio.h"
#include "CPPtester.h"
#include "calogger.h"

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

class test_calogger_class
    : public caTester
{
    CA_TEST_SUITE(test_calogger_class);
    CA_TEST(test_calogger_class::test3, "logs");
    CA_TEST(test_calogger_class::test4, "macro");
    CA_TEST(test_calogger_class::test5, "level");
    CA_TEST_SUITE_END();
    void setUp(void);
    void tearDown(void);
    void test1(void);
    void test2(void);
    void test3(void);
    void test4(void);
    void test5(void);
    CA::ILogger *logger;
    CA::IPrinter *printer;
};
///////////////////////////////////////////////////

REGISTER_CLASS(test_calogger_class);



void test_calogger_class::setUp(void)
{
    logger = new CA::Logger();
    CA_ASSERT(logger!=nullptr);
    printer = new CA::DefaultPrinter();
    logger->setOutput(printer);
    CA_ASSERT(printer==logger->output());
}

void test_calogger_class::tearDown(void)
{
    sleep(1);
    delete logger;
}


void test_calogger_class::test3(void)
{
    _START();
    _INFO("verifica interna alla classe: logE");
    _AUTHOR("Coppi Angelo ca logger");
    _STOP();
    logger->log(0,"%s:%d >prova errore livello 0",__func__, __LINE__);
    logger->log(1,"%s:%d >prova errore livello 1",__func__, __LINE__);
    logger->log(2,"%s:%d >prova errore livello 2",__func__, __LINE__);
    logger->log(3,"%s:%d >prova errore livello 3",__func__, __LINE__);
    logger->log(4,"%s:%d >prova errore livello 4",__func__, __LINE__);
    logger->log(5,"%s:%d >prova errore livello 5",__func__, __LINE__);
    logger->log(6,"%s:%d >prova errore livello 6",__func__, __LINE__);
    logger->log(7,"%s:%d >prova errore livello 7",__func__, __LINE__);
    logger->log(8,"%s:%d >prova errore livello 8",__func__, __LINE__);
    logger->log(9,"%s:%d >prova errore livello 9",__func__, __LINE__);
    logger->log(10,"%s:%d >prova errore livello 10",__func__, __LINE__);
}


void test_calogger_class::test4(void)
{
    _START();
    _INFO("verifica interna alla classe: macro");
    _AUTHOR("Coppi Angelo ca logger");
    _STOP();
    LogEmergency("%s:%d >prova errore livello 0",__func__, __LINE__);
    LogAlert("%s:%d >prova errore livello 1",__func__, __LINE__);
    LogCritical("%s:%d >prova errore livello 2",__func__, __LINE__);
    LogError("%s:%d >prova errore livello 3",__func__, __LINE__);
    LogWarning("%s:%d >prova errore livello 4",__func__, __LINE__);
    LogNotice("%s:%d >prova errore livello 5",__func__, __LINE__);
    LogInfo("%s:%d >prova errore livello 6",__func__, __LINE__);
    LogDebug("%s:%d >prova errore livello 6",__func__, __LINE__);
}
void test_calogger_class::test5(void)
{
    _START();
    _INFO("verifica interna alla classe: macro");
    _AUTHOR("Coppi Angelo ca logger");
    _STOP();
    logger->setLogLevel(3);
    CA_ASSERT(logger->getLogLevel()==3);
    LogEmergency("%s:%d >prova errore livello 0",__func__, __LINE__);
    LogAlert("%s:%d >prova errore livello 1",__func__, __LINE__);
    LogCritical("%s:%d >prova errore livello 2",__func__, __LINE__);
    LogError("%s:%d >prova errore livello 3",__func__, __LINE__);
    LogWarning("%s:%d >prova errore livello 4",__func__, __LINE__);
    LogNotice("%s:%d >prova errore livello 5",__func__, __LINE__);
    LogInfo("%s:%d >prova errore livello 6",__func__, __LINE__);
    LogDebug("%s:%d >prova errore livello 6",__func__, __LINE__);
}
