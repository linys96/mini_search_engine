#ifndef __WEBPAGE_HPP__
#define __WEBPAGE_HPP__

#include <string>
#include <map>

namespace lys
{

class SplitTool;
class Configuration;

class WebPage
{
    friend bool operator==(const WebPage &lhs, const WebPage &rhs);
    friend bool operator<(const WebPage &lhs, const WebPage &rhs);
public:
    WebPage(std::string &doc, Configuration &conf, SplitTool *splitTool);
    ~WebPage() {}

    int getDocId()
    {
        return _docId;
    }
    std::string getDoc()
    {
        return _doc;
    }
    std::map<std::string, int> &getWordsMap()
    {
        return _wordsMap;
    }
private:
    void processDoc(const std::string &doc, Configuration &conf, SplitTool* splitTool);
private:
    std::string _doc;
    int _docId;
    std::string _docTitle;
    std::string _docUrl;
    std::string _docContent;

    std::map<std::string, int> _wordsMap;
};

}//end of namespace lys

#endif
