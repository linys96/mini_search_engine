#include "../include/RssReader.hpp"
#include <iostream>
#include <sstream>
#include <regex>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ostringstream;
using std::shared_ptr;
using std::regex;

namespace lys
{
//处理语料库
void RssReader::handleCorpusFiles()
{
    for(auto &filename : _files) {
        handleCorpusFile(filename);
    }
}
//处理单个文件
void RssReader::handleCorpusFile(string &filename)
{
    XMLDocument doc;
    doc.LoadFile(filename.c_str());
    cout << "begin to handle: " << filename << endl;

    XMLError errorID = doc.ErrorID();
    if(errorID) {
        cout << "XMLDocument LoadFile error!" << endl;
        return;
    } else {
        parseRss(doc);
    }
}

void RssReader::makeDocs(std::vector<std::string> &docs)
{
    for(size_t idx = 0; idx != _items.size(); ++idx) {
        ostringstream oss;
        oss << "<doc>\n" 
            << "  <docid>" << (idx+1) << "</docid>\n"
            << "  <title>" << _items[idx]->_title << "</title>\n"
            << "  <link>"  << _items[idx]->_link  << "</link>\n"
            << "  <content>" << _items[idx]->_content << "</content>\n"
            << "</doc>\n";
        
        string doc = oss.str();
        docs.push_back(doc);
    }
}

void RssReader::parseRss(XMLDocument &doc)
{
    XMLElement *root = doc.FirstChildElement();
    //<channel>
    XMLElement *channel = root->FirstChildElement("channel");
    //<item>
    XMLElement *item = channel->FirstChildElement("item");

    for( ; item; item = item->NextSiblingElement()) {
        shared_ptr<RssItem> rssItemPtr(new RssItem);
        const char *itemTitle = item->FirstChildElement("title")->GetText();
        const char *itemLink = item->FirstChildElement("link")->GetText();
        const char *itemDescription = item->FirstChildElement("description")->GetText();
        const char *itemContent = nullptr;
        XMLElement *contentEncoded = item->FirstChildElement("content:encode");
        if(contentEncoded) {
            itemContent = contentEncoded->GetText();
        } else {
            itemContent = itemDescription;
        }

        regex re("<.+?>");
        string processedContent = std::regex_replace(itemContent, re, ""); 

        rssItemPtr->_title = itemTitle ? itemTitle : string("");
        rssItemPtr->_link = itemLink ? itemLink : string("");
        rssItemPtr->_content = processedContent;

        _items.push_back(rssItemPtr);

    }
}

}//end of namespace lys
