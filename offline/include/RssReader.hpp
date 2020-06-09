#ifndef __RSSREADER_HPP__
#define __RSSREADER_HPP__

#include "../include/tinyxml2.h"

#include <string>
#include <vector>
#include <memory>

namespace lys
{

using namespace tinyxml2;

struct RssItem
{
    std::string _title;
    std::string _link;
    std::string _content;
};

class RssReader
{
public:
    RssReader(std::vector<std::string> &files)
    :_files(files)
    {}
    ~RssReader() {}
    
    void handleCorpusFiles();
    void makeDocs(std::vector<std::string> &docs);

private:
    void handleCorpusFile(std::string &filename);
    void parseRss(XMLDocument &doc);
private:
    std::vector<std::shared_ptr<RssItem>> _items;
    std::vector<std::string> &_files;
};

}//end of namespace lys

#endif
