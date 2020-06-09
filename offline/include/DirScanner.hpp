#ifndef __DIRSCANNER_HPP__
#define __DIRSCANNER_HPP__

#include <string>
#include <vector>

namespace lys
{

class Configuration;

class DirScanner
{
public:
    DirScanner(Configuration &conf);
    ~DirScanner() {}
    std::vector<std::string> &files();
    void operator()();  //重载函数调用运算符，调用traverse函数
private:
    void traverse(const std::string &dirname);  //获取目录下的所有文件
private:
    Configuration &_conf;
    std::vector<std::string> _vecFiles; //存放语料库的绝对路径

};

}//end of namespace lys

#endif
