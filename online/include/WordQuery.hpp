#ifndef __WORDQUERY_HPP__
#define __WORDQUERY_HPP__

#include "WebPage.hpp"
#include "WordSegmentation.hpp"
#include <vector>
#include <unordered_map>
#include <string>
#include <set>

namespace lys
{

class Configuration;

class WordQuery
{
public:
    WordQuery(Configuration &conf);
    ~WordQuery() {}

    std::string doQuery(const std::string &str); //执行查询，返回结果
private:
    void loadLibrary(); //加载库文件
    std::vector<double> getQueryWordsWeightVector(std::vector<std::string> &queryWord);
    bool executeQuery(const std::vector<std::string> &queryWord, 
                      std::vector<std::pair<int,std::vector<double>>> &resultVec);
    std::string createJson(std::vector<int> &docIdVec,
                           const std::vector<std::string> &queryWord);
    std::string returnNoAnswer();
private:
    WordSegmentation _jieba;
    Configuration &_conf;
    std::unordered_map<int, WebPage> _pageLib;
    std::unordered_map<int, std::pair<int, int>> _offsetLib;
    std::unordered_map<std::string, std::set<std::pair<int, double>>> _invertIndexTable;
};

}//end of namespace lys

#endif
