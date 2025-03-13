#include "../../include/utils/utils.h"

using namespace ns_utils;

bool FileUtils::readFile(const std::string &filePath,std::string *result)
{
    std::ifstream in(filePath,std::ios::in);
    if(!in.is_open())
    {
        std::cerr<<filePath<<" open fail"<<std::endl;
        return false;
    }
    std::string line;
    while(std::getline(in,line))
    {
        *result += line;
    }

    in.close();
    return true;
}

//@target:包含文档标题、内容、url的字符串
//@outString:传回拆分的字符串内容，{title,content,url}
//@sep:拆分标识符
//将文件内容按照分割符sep切割
void StringUtils::cutString(const std::string &target,std::vector<std::string> *outString,const std::string &sep)
{
    //使用boost库spilt函数
    boost::split(*outString,target,boost::is_any_of(sep),boost::token_compress_on);
}

//使用jieba分词工具提取关键词
//@src:已经拆分出来的title、content或者url
//@words:分出来的关键词
cppjieba::Jieba JiebaUtils::jieba(DICT_PATH,HMM_PATH,USER_DICT_PATH,IDF_PATH,STOP_WORD_PATH);
void JiebaUtils::extractWords(const std::string &src,std::vector<std::string> *words)
{
    jieba.CutForSearch(src, *words);
}