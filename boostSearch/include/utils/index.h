#ifndef __INDEX_H__
#define __INDEX_H__
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "../types.h"
#include "parserOption.h"

namespace ns_index
{
    // 索引，包含正排索引和倒排索引
    class index
    {
    public:
        index() {}
        ~index() {}

        //根据去标签和格式化后的文件，构建正排索引和倒排索引
        //@rawFilePath:raw.txt的路径，raw.txt是处理格式化后的文件
        bool buildIndex(const std::string &rawFilePath)
        {
            
        }

        // 根据docID获得文档内容
        docInfo *getForwardIndex(const uint64_t &docID)
        {
            if (docID >= forwardIndex.size())
            {
                return nullptr;
            }
            return nullptr;
        }

        invertedList_t *getInvertedList(const std::string &keyWord)
        {

            return nullptr;
        }

    private:
        // 正排索引用类似于数组，数组的下标为文档的id
        std::vector<docInfo> forwardIndex;

        // 倒排索引是关键字和一组invertedElem对应  -->  关键字 : 倒排拉链
        std::unordered_map<std::string, invertedList_t> invertedIndex;
    };
};

#endif