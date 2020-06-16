#ifndef __PAGELIBPREPROCESSOR_HPP__
#define __PAGELIBPREPROCESSOR_HPP__

#include "WebPage.hpp"
#include <vector>
#include <string>
#include <unordered_map>

namespace lys
{

class Configuration;
class SplitTool;

class PageLibPreprocessor
{
public:
    PageLibPreprocessor(Configuration &conf, SplitTool *jieba)
    :_conf(conf)
    ,_jieba(jieba)
    {}
    ~PageLibPreprocessor() {}

    void doProcess();
private:
    void readInfoFromFile();
    void cutRepeatedPages();
    void buildInvertIndexTable();
    void storeOnDisk();
private:
    Configuration &_conf;
    SplitTool *_jieba;
    std::vector<WebPage> _pageLib;
    std::unordered_map<int, std::pair<int, int>> _offsetLib;
    std::unordered_map<std::string, std::vector<std::pair<int, double>>> _invertIndexTable;
};

}//end of namespace lys

#endif
