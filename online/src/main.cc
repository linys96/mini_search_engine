#include "../include/WordQueryServer.hpp"
#include "../include/Configuration.hpp"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

int main(int argc,char *argv[])
{
    lys::Configuration conf("../conf/server.conf");
    lys::WordQueryServer wqServer(conf);
    wqServer.start();
    return 0;
}

