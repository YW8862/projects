#ifndef __TYPES_H__
#define __TYPES_H__
#include <iostream>
#include <string>
#include <vector>

//文档对象结构体
class docInfo_t
{
private:
    std::string title;   //文档标题
    std::string content; //文档内容
    std::string url;     //该文档在官网中的url
};

//正排索引元素结构体
class docInfo
{
public:
    std::string title;   //文档标题
    std::string content; //文档内容
    std::string url;     //该文档在官网中的url
    uint64_t docId;
};

//倒排索引元素结构体
class invertedElem
{
    int docId;              //文档id
    std::string keyWord;    //关键词
    double weight;          //关键词权重
};

//一组倒排文档组成一个倒排映射对象 --> 倒排拉链
using invertedList_t = std::vector<invertedElem>;


#endif