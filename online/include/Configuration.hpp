#ifndef __CONFIGURATION_HPP__
#define __CONFIGURATION_HPP__

#include <string>
#include <map>
#include <unordered_set>

namespace lys
{

class Configuration
{
public:
    Configuration(const std::string &filepath);
    ~Configuration(){}
    
    std::map<std::string,std::string> &getConfigMap();
    std::unordered_set<std::string> &getStopWordList();
private:
    std::string _filepath;  //配置文件路径 
    std::map<std::string,std::string> _configMap;   //配置文件内容
    std::unordered_set<std::string> _stopWordList; //停用词词集
};

}//end of namespace lys

#endif


