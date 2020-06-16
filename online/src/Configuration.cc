#include "../include/Configuration.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using std::map;
using std::string;
using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;

namespace lys
{

Configuration::Configuration(const std::string &filepath)
:_filepath(filepath)
{
    //读取配置文件
    ifstream ifs(filepath);
    if(!ifs.good()){
       cout << "Configuration file open error!" << endl;
       return;
    }

    string line, key ,value;

    while(getline(ifs,line)){
        istringstream iss(line);
        iss >> key >> value;
        _configMap[key] = value;
    }
    ifs.close();

}

std::map<std::string,std::string> &Configuration::getConfigMap()
{

    return _configMap;
}


std::unordered_set<std::string> &Configuration::getStopWordList()
{
    //读取停用词
    ifstream ifsStopWord(_configMap["STOP_WORD_PATH"]);

    if(!ifsStopWord.good()){
       cout << "StopWord file open error!" << endl;
    }
    string stopWord;
    while(getline(ifsStopWord, stopWord)) {
        _stopWordList.insert(stopWord);
    }

    ifsStopWord.close();

    return _stopWordList;
}

}//end of namespace lys
