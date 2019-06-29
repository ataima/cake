#include <stdio.h>
#include <string>
#include <sys/stat.h>
#include "CPPtester.h"
#include "caminiXml.h"


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

///////////////////// HEADER //////////////////////

class test_miniXml_class
    : public caTester
{
    CA_TEST_SUITE(test_miniXml_class)
    CA_TEST(test_miniXml_class::test1, "xlnode");
    CA_TEST(test_miniXml_class::test2, "xlnode");
    CA_TEST(test_miniXml_class::test3, "xlnode");
    CA_TEST(test_miniXml_class::test4, "xlnode");
    CA_TEST(test_miniXml_class::test5, "xlnode");
    CA_TEST(test_miniXml_class::test6, "xlnode");
    CA_TEST(test_miniXml_class::test7, "xlnode");
    CA_TEST(test_miniXml_class::test8, "type");
    CA_TEST(test_miniXml_class::test9, "index");
    CA_TEST(test_miniXml_class::test10, "index");
    CA_TEST(test_miniXml_class::test11, "exfile");
    CA_TEST_SUITE_END()
    void setUp(void);
    void tearDown(void);
    void test1(void);
    void test2(void);
    void test3(void);
    void test4(void);
    void test5(void);
    void test6(void);
    void test7(void);
    void test8(void);
    void test9(void);
    void test10(void);
    void test11(void);
};
///////////////////////////////////////////////////

REGISTER_CLASS(test_miniXml_class);

void test_miniXml_class::setUp(void)
{
    rmdir("/tmp/tests");
    mkdir("/tmp/tests",S_IRWXU | S_IRWXG );
}

void test_miniXml_class::tearDown(void)
{
    rmdir("/tmp/tests");
}


static FILE *filetest(const char *name)
{
    char buff[512];
    sprintf(buff,"/tmp/tests/%s",name);
    FILE *f = fopen(buff, "w+");
    if(f==nullptr)
    {
        CA_ASSERT(false);
    }
    return f;
}

void test_miniXml_class::test1(void)
{
    _START();
    _INFO("create XmlNode");
    _AUTHOR("Coppi Angelo qxml library ");
    _STOP();

    CA::miniXmlNode root("ROOT", "");
    CA::miniXmlNode* child1 = dynamic_cast<CA::miniXmlNode*> (root.add("child1", "1000"));
    CA::miniXmlNode* child2 = dynamic_cast<CA::miniXmlNode*> (child1->add("child2", "2000"));
    root.print(stdout);
    CA_ASSERT(root.getParent() == nullptr);
    CA_ASSERT(root.getChild() == child1);
    CA_ASSERT(root.getNext() == nullptr);
    CA_ASSERT(child1->getChild() == child2);
}

void test_miniXml_class::test2(void)
{
    _START();
    _INFO("create XmlNode");
    _AUTHOR("Coppi Angelo qxml library ");
    _STOP();

    CA::miniXmlNode root("ROOT", "");
    CA::IXmlNode* child1 = root.add("child1", "1000");
    CA::IXmlNode* child2 = root.add("child2", "2000");
    root.print(stdout);
    CA_ASSERT(root.getParent() == nullptr);
    CA_ASSERT(root.getChild() == child1);
    CA_ASSERT(root.getNext() == nullptr);
    CA_ASSERT(child1->getNext() == child2);
}

void test_miniXml_class::test3(void)
{
    _START();
    _INFO("parse XmlNode");
    _AUTHOR("Coppi Angelo qxml library ");
    _STOP();
    const char *xml = "<ROOT>\r\n<child1>\r\n1000\r\n</child1>\r\n<child2>\r\n2000\r\n</child2>\r\n</ROOT>\r\n";
    FILE *f = filetest("test3.xml");
    fwrite(xml, sizeof (char), strlen(xml), f);
    fclose(f);
    CA::miniXmlNode root("","");
    root.load("/tmp/tests/test3.xml");
    root.print(stdout);
    CA_ASSERT(root.find("child1") != nullptr);
    CA_ASSERT(root.find("child2") != nullptr);
}

void test_miniXml_class::test4(void)
{
    _START();
    _INFO("create XmlNode and parse");
    _AUTHOR("Coppi Angelo qxml library ");
    _STOP();

    CA::miniXmlNode root("ROOT", "");
    CA::IXmlNode* child1 = root.add("child1", "1000");
    CA::IXmlNode* child2 = root.add("child2", "2000");
    CA::IXmlNode* child3 = root.add("child3", "3000");
    CA::IXmlNode* child4 = root.add("child4", "4000");
    CA::IXmlNode* child5 = root.add("child5", "5000");
    CA_ASSERT(root.getParent() == nullptr);
    CA_ASSERT(root.getChild() == child1);
    CA_ASSERT(root.getNext() == nullptr);
    CA_ASSERT(child1->getNext() == child2);
    root.print(stdout);
    FILE *f = filetest("test4.xml");
    root.print(f);
    fclose(f);
    CA::miniXmlNode root1("","");
    root1.load("/tmp/tests/test4.xml");
    root1.print(stdout);
    CA_ASSERT(root1.find("child1") != nullptr);
    CA_ASSERT(root1.find("child2") != nullptr);
    CA_ASSERT(root1.find("child3") != nullptr);
    CA_ASSERT(root1.find("child4") != nullptr);
    CA_ASSERT(root1.find("child5") != nullptr);
}

void test_miniXml_class::test5(void)
{
    _START();
    _INFO("create XmlNode and parse");
    _AUTHOR("Coppi Angelo qxml library ");
    _STOP();
    CA::miniXmlNode root("ROOT", "");
    CA::IXmlNode* child1 = root.add("child1", "1000");
    CA::IXmlNode* child2 = root.add("child1.child2", "2000");
    CA::IXmlNode* child3 = root.add("child1.child2.child3", "3000");
    CA::IXmlNode* child4 = root.add("child1.child2.child3.child4", "4000");
    CA::IXmlNode* child5 = root.add("child1.child2.child3.child4.child5", "5000");
    CA_ASSERT(root.getParent() == nullptr);
    CA_ASSERT(root.getChild() == child1);
    CA_ASSERT(root.getNext() == nullptr);
    CA_ASSERT(child1->getNext() == nullptr);
    CA_ASSERT(child1->getChild() == child2);
    root.print(stdout);
    FILE *f = filetest("test5.xml");
    root.print(f);
    fclose(f);
    CA::miniXmlNode root1("","");
    root1.load("/tmp/tests/test5.xml");
    root1.print(stdout);
    CA_ASSERT(root1.find("child1") != nullptr);
    CA_ASSERT(root1.find("child1.child2") != nullptr);
    CA_ASSERT(root1.find("child1.child2.child3") != nullptr);
    CA_ASSERT(root1.find("child1.child2.child3.child4") != nullptr);
    CA_ASSERT(root1.find("child1.child2.child3.child4.child5") != nullptr);
}

void test_miniXml_class::test6(void)
{
    _START();
    _INFO("create XmlNode and parse");
    _AUTHOR("Coppi Angelo qxml library ");
    _STOP();

    CA::miniXmlNode root("ROOT", "1000");
    CA::IXmlNode* child1 = root.add("child1", "1000");
    CA::IXmlNode* child2 = root.add("child2", "2000");
    CA_ASSERT(root.getParent() == nullptr);
    CA_ASSERT(root.getChild() == child1);
    CA_ASSERT(root.getNext() == nullptr);
    CA_ASSERT(child1->getNext() == child2);
    root.print(stdout);
    FILE *f = filetest("test6.xml");
    root.print(f);
    fclose(f);
    CA::miniXmlNode root1("","");
    root1.load("/tmp/tests/test6.xml");
    root1.print(stdout);
    CA_ASSERT(root1.getValue() == "1000");
    CA_ASSERT(root1.find("child1") != nullptr);
    CA_ASSERT(root1.find("child1")->getLong() == 1000);
    CA_ASSERT(root1.find("child2") != nullptr);
    CA_ASSERT(root1.find("child2")->getLong() == 2000);
}

void test_miniXml_class::test7(void)
{
    _START();
    _INFO("create XmlNode and parse and get num item");
    _AUTHOR("Coppi Angelo qxml library ");
    _STOP();
    CA::miniXmlNode root("ROOT", "");
    CA::IXmlNode* child1 = root.add("child1", "1000");
    CA::IXmlNode* child2 = root.add("child1.child2", "2000");
    CA::IXmlNode* child3 = root.add("child1.child2", "3000");
    CA::IXmlNode* child4 = root.add("child1.child2", "4000");
    CA::IXmlNode* child5 = root.add("child1.child2", "5000");
    CA_ASSERT(root.getParent() == nullptr);
    CA_ASSERT(root.getChild() == child1);
    CA_ASSERT(root.getNext() == nullptr);
    CA_ASSERT(child1->getNext() == nullptr);
    CA_ASSERT(child1->getChild() != nullptr);
    root.print(stdout);
    CA_ASSERT(child1->getChildName("child2")==4);
}


void test_miniXml_class::test8(void)
{
    _START();
    _INFO("create XmlNode and test node type");
    _AUTHOR("Coppi Angelo qxml library ");
    _STOP();
    CA::miniXmlNode root("ROOT", "");
    CA::IXmlNode* child1 = root.add("child1", "1000");
    CA_ASSERT(root.getNodeType()==CA::IXmlNode::xmlNodeType::inode_childs);
    CA_ASSERT(child1->getNodeType()==CA::IXmlNode::xmlNodeType::inode_simple);
    CA::IXmlNode* child2 = root.add("child1.child2", "2000");
    CA_ASSERT(root.getNodeType()==CA::IXmlNode::xmlNodeType::inode_childs);
    CA_ASSERT(child1->getNodeType()==CA::IXmlNode::xmlNodeType::inode_childs);
    CA_ASSERT(child2->getNodeType()==CA::IXmlNode::xmlNodeType::inode_simple);

    CA::IXmlNode* child1_1 = root.add("child1", "3000");
    CA_ASSERT(root.getNodeType()==CA::IXmlNode::xmlNodeType::inode_childs);
    CA_ASSERT(child1->getNodeType()==CA::IXmlNode::xmlNodeType::inode_array_childs);
    CA_ASSERT(child2->getNodeType()==CA::IXmlNode::xmlNodeType::inode_simple);
    CA_ASSERT(child1_1->getNodeType()==CA::IXmlNode::xmlNodeType::inode_array);
    CA_ASSERT(root.getParent() == nullptr);
    CA_ASSERT(root.getChild() == child1);
    CA_ASSERT(child1->getNext() == child1_1);
    CA_ASSERT(root.getNext() == nullptr);
    CA_ASSERT(child1->getChild() != nullptr);
    CA_ASSERT(child1_1->getNext() == nullptr);
    CA_ASSERT(child1_1->getChild() == nullptr);
    CA::IXmlNode* child3 = child1_1->add("child3", "2001");
    CA_ASSERT(child3->getNodeType()==CA::IXmlNode::xmlNodeType::inode_simple);
    CA_ASSERT(child1_1->getNodeType()==CA::IXmlNode::xmlNodeType::inode_array_childs);
    root.print(stdout);

}

void test_miniXml_class::test9(void)
{
    _START();
    _INFO("create XmlNode and test node type and index");
    _AUTHOR("Coppi Angelo qxml library ");
    _STOP();
    CA::miniXmlNode root("ROOT", "");
    CA::IXmlNode* child1 = root.add("child1", "1000");
    CA_ASSERT(root.getNodeType()==CA::IXmlNode::xmlNodeType::inode_childs);
    CA_ASSERT(child1->getNodeType()==CA::IXmlNode::xmlNodeType::inode_simple);
    CA_ASSERT(root.getIndex()==0);
    CA_ASSERT(child1->getIndex()==0);
    CA::IXmlNode* child2 = root.add("child1.child2", "2000");
    CA_ASSERT(root.getNodeType()==CA::IXmlNode::xmlNodeType::inode_childs);
    CA_ASSERT(child1->getNodeType()==CA::IXmlNode::xmlNodeType::inode_childs);
    CA_ASSERT(child2->getNodeType()==CA::IXmlNode::xmlNodeType::inode_simple);
    CA_ASSERT(root.getIndex()==0);
    CA_ASSERT(child1->getIndex()==0);
    CA_ASSERT(child2->getIndex()==0);
    CA::IXmlNode* child1_1 = root.add("child1", "3000");
    CA_ASSERT(root.getNodeType()==CA::IXmlNode::xmlNodeType::inode_childs);
    CA_ASSERT(child1->getNodeType()==CA::IXmlNode::xmlNodeType::inode_array_childs);
    CA_ASSERT(child2->getNodeType()==CA::IXmlNode::xmlNodeType::inode_simple);
    CA_ASSERT(child1_1->getNodeType()==CA::IXmlNode::xmlNodeType::inode_array);
    CA_ASSERT(root.getIndex()==0);
    CA_ASSERT(child1->getIndex()==0);
    CA_ASSERT(child2->getIndex()==0);
    CA_ASSERT(child1_1->getIndex()==1);
    CA_ASSERT(root.getParent() == nullptr);
    CA_ASSERT(root.getChild() == child1);
    CA_ASSERT(child1->getNext() == child1_1);
    CA_ASSERT(root.getNext() == nullptr);
    CA_ASSERT(child1->getChild() != nullptr);
    CA_ASSERT(child1_1->getNext() == nullptr);
    CA_ASSERT(child1_1->getChild() == nullptr);
    CA::IXmlNode* child3 = child1_1->add("child3", "2001");
    CA_ASSERT(child3->getNodeType()==CA::IXmlNode::xmlNodeType::inode_simple);
    CA_ASSERT(child1_1->getNodeType()==CA::IXmlNode::xmlNodeType::inode_array_childs);
    CA_ASSERT(root.getIndex()==0);
    CA_ASSERT(child1->getIndex()==0);
    CA_ASSERT(child2->getIndex()==0);
    CA_ASSERT(child1_1->getIndex()==1);
    root.print(stdout);

}


void test_miniXml_class::test10(void)
{
    _START();
    _INFO("create XmlNode and test node type and index");
    _AUTHOR("Coppi Angelo qxml library ");
    _STOP();
    CA::miniXmlNode root("ROOT", "");
    CA::IXmlNode* child1 = root.add("child1", "1000");
    CA_ASSERT(root.getNodeType()==CA::IXmlNode::xmlNodeType::inode_childs);
    CA_ASSERT(child1->getNodeType()==CA::IXmlNode::xmlNodeType::inode_simple);
    CA_ASSERT(root.getIndex()==0);
    CA_ASSERT(child1->getIndex()==0);
    CA::IXmlNode* child2 = root.add("child1.child2", "2000");
    int i=0;
    for(i=0; i<100; i++)
    {
        CA::IXmlNode* childn=root.add("child1", "1000");
        CA_ASSERT(child1->getNodeType()==CA::IXmlNode::xmlNodeType::inode_array_childs);
        CA_ASSERT(childn->getNodeType()==CA::IXmlNode::xmlNodeType::inode_array);
        child2 = childn->add("child1.child2", "2000");
        CA_ASSERT(childn->getNodeType()==CA::IXmlNode::xmlNodeType::inode_array_childs);
        CA_ASSERT(childn->getIndex()==i+1);
    }
    root.print(stdout);

}

void test_miniXml_class::test11(void)
{
    _START();
    _INFO("create XmlNode try to laod testfiles/file5.xml");
    _AUTHOR("Coppi Angelo qxml library ");
    _STOP();
    CA::miniXmlNode root("", "");
    root.load("/home/angelo/workspace/qxmlc/testfiles/file7.xml");
    CA::IXmlNode *nset=root.find("egg.project.build.step.path.pre.set");
    CA_ASSERT(nset != nullptr);
    nset->print(stdout);
    nset=root.find("egg.project.build.step.path.set");
    CA_ASSERT(nset == nullptr);

}
