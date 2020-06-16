#include "../include/Configuration.hpp"
#include "../include/DirScanner.hpp"
#include "../include/PageLib.hpp"
#include "../include/PageLibPreprocessor.hpp"
#include "../include/SplitToolJieba.hpp"
#include <iostream>

using std::cout;
using std::endl;

void test0()
{
    using namespace lys;
    Configuration conf("../conf/myconf.conf");

    DirScanner dirScanner(conf);
    dirScanner();

    PageLib pageLib(conf, dirScanner);
    pageLib.create();
    pageLib.store();

    SplitTool *pjieba = new SplitToolCppJieba(conf);
    PageLibPreprocessor preProcessor(conf, pjieba);
    preProcessor.doProcess();
    delete pjieba;
}
int main(int argc,char *argv[])
{
    test0();
    return 0;
}

