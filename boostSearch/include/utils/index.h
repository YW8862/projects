#ifndef __INDEX_H__
#define __INDEX_H__
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <thread>
#include <mutex>
#include "parserOption.h"
#include "../../include/utils/utils.h"
#include "../types.h"

namespace ns_index
{
    // 索引，包含正排索引和倒排索引
    class index
    {
    public:
        ~index() {}

        static index *getInstance();

        // 根据去标签和格式化后的文件，构建正排索引和倒排索引
        //@rawFilePath:raw.txt的路径，raw.txt是处理格式化后的文件
        bool buildIndex(const std::string &rawFilePath);

        // 根据docID获得文档内容
        docInfo *getForwardIndex(const uint64_t &docID);

        // 根据倒关键字引获取倒排拉链
        invertedList_t *getInvertedList(const std::string &keyWord);

    private:
        // 建立正排索引
        docInfo *buildForwardIndex(const std::string &doc);

        // 建立倒排索引
        bool buildInvertedIndex(const docInfo &doc);

        index() {}

        // 禁用赋值和拷贝构造
        index(const index &_index) = delete;

        index &operator=(const index &_index) = delete;

    private:
        // 正排索引用类似于数组，数组的下标为文档的id
        std::vector<docInfo> forwardIndex;

        // 倒排索引是关键字和一组invertedElem对应  -->  关键字 : 倒排拉链
        std::unordered_map<std::string, invertedList_t> invertedIndex;

        static index *instance;
        static std::mutex gmutex;
    };

    //extern index *index::instance;
    //extern std::mutex gmutex;
};

#endif