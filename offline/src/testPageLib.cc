#include "../include/Configuration.hpp"
#include "../include/DirScanner.hpp"
#include "../include/PageLib.hpp"
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
}
int main(int argc,char *argv[])
{
    test0();
    return 0;
}

