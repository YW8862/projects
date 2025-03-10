#ifndef __PARSEROPTION_H__
#define __PARSEROPTION_H__

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <boost/filesystem.hpp>
#include "../types.h"

//定义同一个文件中的title、content、url的分隔符
#define SEP '\3'

const std::string srcPath = "./data/input";
const std::string rawPath = "./data/raw_html/raw.txt";

enum
{
    ENUMFILE = 1,
    PARSERERROR,
    SAVEERROR
};

//const &:输入参数
//*:输出参数
//&输入输出参数

bool enumFiles(const std::string &srcPath, std::vector<std::string> *filesList);
bool parseHtml(const std::vector<std::string> &filesList, std::vector<docInfo_t> *results);
bool save(const std::vector<docInfo_t> &results, const std::string &rawPath);

#endif