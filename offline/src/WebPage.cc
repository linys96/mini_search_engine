#include "../include/WebPage.hpp"
#include "../include/SplitToolJieba.hpp"
#include "../include/Configuration.hpp"

#include "../include/simhash/Simhasher.hpp"

#include <iostream>
#include <vector>
#include <unordered_set>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::unordered_set;

namespace lys
{

WebPage::WebPage(std::string &doc, Configuration &conf, SplitTool *splitTool)
:_doc(doc)
{
    /* cout << "WebPage(std::string &doc, Configuration &conf, SplitTool *splitTool)" << endl; */
    processDoc(doc, conf, splitTool);
}

void WebPage::processDoc(const std::string &doc, Configuration &conf, SplitTool* splitTool)
{
	string docIdHead = "<docid>";
	string docIdTail = "</docid>";
	string docUrlHead = "<link>";
	string docUrlTail = "</link>";
	string docTitleHead = "<title>";
	string docTitleTail = "</title>";
	string docContentHead = "<content>";
	string docContentTail = "</content>";

	//提取文档的docid
	int bpos = doc.find(docIdHead);
	int epos = doc.find(docIdTail);
	string docId = doc.substr(bpos + docIdHead.size(), 
					epos - bpos - docIdHead.size());
	_docId = atoi(docId.c_str());

	//title
	bpos = doc.find(docTitleHead);
	epos = doc.find(docTitleTail);
	_docTitle = doc.substr(bpos + docTitleHead.size(), 
					epos - bpos - docTitleHead.size());

	//cout << "========" << endl << _docTitle << endl;
	//content
	bpos = doc.find(docContentHead);
	epos = doc.find(docContentTail);
	_docContent = doc.substr(bpos + docContentHead.size(),
					epos - bpos - docContentHead.size());

	//cout << "========" << endl << _docContent << endl;


	//分词、统计词频
    /* cout << "before cut" << endl; */
	vector<string> wordsVec = splitTool->cut(_docContent);
    /* cout << "after cut" << endl; */
    
    unordered_set<string> &stopWordList = conf.getStopWordList();

    for(auto &word: wordsVec) {
        auto iter = stopWordList.find(word);
        if(iter == stopWordList.end()) {
            ++_wordsMap[word];
        }
    }
    
}

bool operator==(const WebPage &lhs, const WebPage &rhs)
{
    using namespace simhash;

    Simhasher simhasher("../dict/jieba.dict.utf8", "../dict/hmm_model.utf8", "../dict/idf.utf8", "../dict/stop_words.utf8");

    size_t topN = 20;
    uint64_t u1, u2;
    simhasher.make(lhs._docContent, topN, u1);
    simhasher.make(rhs._docContent, topN, u2);

    return simhash::Simhasher::isEqual(u1, u2); 
}

bool operator<(const WebPage &lhs, const WebPage &rhs)
{
    bool flag = false;
    if(lhs._docId < rhs._docId) {
        flag = true;
    }
    return flag;
}


}//end of namespace lys
