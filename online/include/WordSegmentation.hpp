#ifndef __WORD_SEGMENTATION_H__
#define __WORD_SEGMENTATION_H__

#include "cppjieba/Jieba.hpp"

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

namespace lys
{

const char* const DICT_PATH = "../dict/jieba.dict.utf8";
const char* const HMM_PATH = "../dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "../dict/user.dict.utf8";
const char* const IDF_PATH = "../dict/idf.utf8";
const char* const STOP_WORD_PATH = "../dict/stop_words.utf8";

class WordSegmentation
{
public:
	WordSegmentation()
    :_jieba(DICT_PATH,
        HMM_PATH,
        USER_DICT_PATH,
        IDF_PATH,
        STOP_WORD_PATH)
	{
		cout << "cppjieba init!" << endl;
	}


	vector<string> operator()(const char * src)
	{
		vector<string> words;
		_jieba.CutForSearch(src, words);
		return words;
	}

	vector<string> operator()(const string & src)
	{
		vector<string> words;
		_jieba.CutForSearch(src, words);
		return words;
	}

private:
	cppjieba::Jieba _jieba;
};

}// end of namespace lys

#endif
