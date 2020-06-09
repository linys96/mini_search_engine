#include "../include/DirScanner.hpp"
#include "../include/Configuration.hpp"
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

namespace lys
{

DirScanner::DirScanner(Configuration &conf)
:_conf(conf)
{}

std::vector<std::string> &DirScanner::files()
{
    return _vecFiles;
}

//重载函数调用运算符，调用traverse函数
void DirScanner::operator()()
{
    string dirname = _conf.getConfigMap()["CORPUS_DIR"];
    traverse(dirname);
}


//获取目录下的所有文件
void DirScanner::traverse(const std::string &dirname)
{
    DIR *pdir = ::opendir(dirname.c_str());   
    if(NULL == pdir){
        perror("opendir");
        return;
    }
    struct dirent *pDirInfo;
    while( (pDirInfo=readdir(pdir)) != NULL ){
        if(0 == strcmp(pDirInfo->d_name, ".")||
           0 == strcmp(pDirInfo->d_name, "..")){
            continue;
        }
        char tmp[512]={0};
        sprintf(tmp,"%s/%s",dirname.c_str(),pDirInfo->d_name);
        _vecFiles.push_back(string(tmp));
    }
}

}//end of namespace lys
