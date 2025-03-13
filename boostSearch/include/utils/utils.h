#ifndef __READFILE_H__
#define __READFILE_H__
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include "../../thirdpart/cppjieba/Jieba.hpp"

namespace ns_utils
{
    class FileUtils
    {
    public:
        static bool readFile(const std::string &filePath, std::string *result);
    };

    class StringUtils
    {
    public:
        static void cutString(const std::string &target, std::vector<std::string> *outString, const std::string &sep);
    };

    class JiebaUtils
    {
    public:
        static void extractWords(const std::string &src,std::vector<std::string> *words);
    private:
        //定义静态成员jieba对象
        static cppjieba::Jieba jieba;
    };
    const char *const DICT_PATH = "/home/yw/projects/boostSearch/thirdpart/dict/jieba.dict.utf8";
    const char *const HMM_PATH = "/home/yw/projects/boostSearch/thirdpart/dict/hmm_model.utf8";
    const char *const USER_DICT_PATH = "/home/yw/projects/boostSearch/thirdpart/dict/user.dict.utf8";
    const char *const IDF_PATH = "/home/yw/projects/boostSearch/thirdpart/dict/idf.utf8";
    const char *const STOP_WORD_PATH = "/home/yw/projects/boostSearch/thirdpart/dict/stop_words.utf8";
};

#endif