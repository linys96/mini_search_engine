#ifndef __PAGELIB_HPP
#define __PAGELIB_HPP

#include <vector>
#include <string>
#include <unordered_map>

namespace lys
{
class Configuration;
class DirScanner;

class PageLib
{
public:
    PageLib(Configuration &conf, DirScanner &dirScanner)
    :_conf(conf)
    ,_dirScanner(dirScanner)
    {}
    ~PageLib() {}

    void create(); //创建网页库
    void store(); //存储网页库和位置偏移库
private:
    Configuration &_conf;        
    DirScanner &_dirScanner;
    std::vector<std::string> _vecDocs; //存放格式化后的网页
    std::unordered_map<int, std::pair<int, int>> _offsetLib; //存放每篇文档在网页库中的位置信息

};

}// end of namespace lys

#endif
