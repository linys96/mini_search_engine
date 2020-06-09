#include "../include/PageLib.hpp"
#include "../include/DirScanner.hpp"
#include "../include/Configuration.hpp"
#include "../include/RssReader.hpp"
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::map;
using std::ofstream;

namespace lys
{ 
//创建网页库
void PageLib::create()
{
    vector<string> &files = _dirScanner.files();
    RssReader reader(files);
    reader.handleCorpusFiles();
    reader.makeDocs(_vecDocs); 
}

//存储网页库和位置偏移库
void PageLib::store()
{
    //读取配置文件
    map<string, string> & confMap = _conf.getConfigMap();
    string pageLibPath = confMap["RIPE_PAGE_LIB_PATH"];
    string offsetLibPath = confMap["OFFSET_LIB_PATH"];
    ofstream ofsPage(pageLibPath);
    ofstream ofsOffset(offsetLibPath);
    if(!(ofsPage.good() && ofsOffset.good())) {
        cout << "ofs open file error!" << endl;
        return;
    }

    for(size_t idx = 0; idx != _vecDocs.size(); ++idx) {
        int id = idx + 1;
        int fileLenth = _vecDocs[idx].size();
        ofstream::pos_type offset = ofsPage.tellp();

        ofsPage << _vecDocs[idx];
        ofsOffset << id << '\t' << offset << '\t' << fileLenth << '\n';
    }

    ofsPage.close();
    ofsOffset.close();
}

}//end of namespace lys
