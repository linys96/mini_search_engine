#include "../include/PageLibPreprocessor.hpp"
#include "../include/Configuration.hpp"

#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using std::cout;
using std::endl;
using std::map;
using std::string;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::make_pair;
using std::sort;

namespace lys
{

void PageLibPreprocessor::doProcess()
{
    cout << "begin to readInfoFromFile" << endl; 
    readInfoFromFile();
    cout << "begin to cutRepeatedPages" << endl;
    cutRepeatedPages();
    cout << "begin to buildInvertIndexTable" << endl;
    buildInvertIndexTable();
    cout << "begin to storeOnDisk" << endl;
    storeOnDisk();
}

void PageLibPreprocessor::readInfoFromFile()
{
    map<string, string> confMap = _conf.getConfigMap();
    ifstream pageIfs(confMap["RIPE_PAGE_LIB_PATH"]);
    ifstream offsetIfs(confMap["OFFSET_LIB_PATH"]);
    if(!(pageIfs.good() && offsetIfs.good())) {
        cout << "open page or offset lib error!" << endl;
        return;
    }
    

    string line;
    int docId, docOffset, docLen;
    while(getline(offsetIfs,line)) {
        cout << line << endl;
        istringstream iss(line);
        iss >> docId >> docOffset >> docLen;

        string doc;
        doc.resize(docLen, '\0');
        pageIfs.seekg(docOffset, pageIfs.beg);
        pageIfs.read(&*doc.begin(), docLen);

        WebPage webPage(doc, _conf, _jieba);
        _pageLib.push_back(webPage);

        _offsetLib.insert(make_pair(docId, make_pair(docOffset, docLen)));
    }
}

void PageLibPreprocessor::cutRepeatedPages()
{
    for(size_t i = 0; i != _pageLib.size() - 1; ++i) {
        for(size_t j = i + 1; j != _pageLib.size(); ++j) {
            cout << "i=" << i << " j=" << j << "size=" << _pageLib.size() << endl;
            if(_pageLib[i] == _pageLib[j]) {
                _pageLib[j] = _pageLib[_pageLib.size() - 1];
                _pageLib.pop_back();
                --j;
            }
        }
    }
}

void PageLibPreprocessor::buildInvertIndexTable()
{
    for(auto &page: _pageLib) {
        map<string, int> &wordsMap = page.getWordsMap();
        for(auto &wordFreq: wordsMap) {
            _invertIndexTable[wordFreq.first].push_back(
                make_pair(page.getDocId(), wordFreq.second));
        }
    }

    //计算每篇文档中的词的权重，并归一化
    map<int, double> weightSum;
    int totalPageNum = _pageLib.size();
    for(auto &item : _invertIndexTable) {
        int df = item.second.size();
        double idf = log(static_cast<double>(totalPageNum)/df + 0.05) / log(2);
        for(auto &sitem : item.second) {
            double weight = sitem.second * idf;
            weightSum[sitem.first] += pow(weight, 2);
            sitem.second = weight;
        }
    }
    //归一化处理
    for(auto & item : _invertIndexTable) {
        for(auto &sitem : item.second) {
            sitem.second = sitem.second / sqrt(weightSum[sitem.first]);
        }
    }
}

void PageLibPreprocessor::storeOnDisk()
{
    sort(_pageLib.begin(), _pageLib.end());
    ofstream pageLibOfs(_conf.getConfigMap()["NEW_RIPE_PAGE_LIB_PATH"]);
    ofstream offsetOfs(_conf.getConfigMap()["NEW_OFFSET_LIB_PATH"]);
    if(!(pageLibOfs.good() && offsetOfs.good())) {
        cout << "ofs open page or offset lib error!" << endl;
        return;
    }
    for(auto &page : _pageLib) {
        int id = page.getDocId();
        int lenth = page.getDoc().size();
        ofstream::pos_type offset = pageLibOfs.tellp();
        pageLibOfs << page.getDoc();
        offsetOfs << id << '\t' << offset << '\t' << lenth << '\n';
    }
    pageLibOfs.close();
    offsetOfs.close();

    ofstream invertIndexTableOfs(_conf.getConfigMap()["INVERT_INDEX_TABLE_PATH"]);
    if(!invertIndexTableOfs.good()){
        cout << "open invertIndexTable error!" << endl;
        return;
    }
    for(auto &item : _invertIndexTable) {
        invertIndexTableOfs << item.first << '\t';
        for(auto &sitem : item.second) {
            invertIndexTableOfs << sitem.first << '\t' << sitem.second << '\t';
        }
        invertIndexTableOfs << endl;
    }
    invertIndexTableOfs.close();
}

}//end of namespace lys
