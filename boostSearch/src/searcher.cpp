#include "../include/searcher.h"

using namespace ns_searcher;

void Searcher::initSearcher(const std::string &rawFile)
{
    // 1.获取或者创建index对象
    index = ns_index::index::getInstance();
    std::cout << "get Instance..." << std::endl;
    // 2.根据index对象创建索引
    std::cout << "create index..." << std::endl;
    index->buildIndex(rawFile);
}

void Searcher::search(const std::string &query, std::string *jsonString)
{
    // 1.[分词]对query分词
    std::vector<std::string> words;
    ns_utils::JiebaUtils::split(query, &words);
    // 2.[触发]根据分词后的各个词进行查找
    //invertedList_t invertedList;
    std::vector<invertedElemPrint> invertedList;
    std::unordered_map<uint64_t, invertedElemPrint> tokensMap;
    for (std::string word : words)
    {
        boost::to_lower(word);
        // 根据关键词获取倒排拉链
        invertedList_t *list = index->getInvertedList(word);
        // 如果没有关键词对应的倒排拉链
        if (list == nullptr)
        {
            continue;
        }
        // invertedList.insert(invertedList.end(), list->begin(), list->end());
        //去重
        for (auto &elem : *list)
        {
            //如果存在，直接获取，否则创建
            auto &item = tokensMap[elem.docId]; 
            //item一定是docID相同的节点
            item.docId = elem.docId;
            item.weight += elem.weight;
            item.words.push_back(elem.keyWord);
        }
    }
    //去重合并后插入
    for(const auto &elem:tokensMap)
    {
        invertedList.push_back(std::move(elem.second));
    }
    // 3.[合并排序]根据汇总的查找结果按照相关性进行降序排序
    std::sort(invertedList.begin(), invertedList.end(), [](const invertedElemPrint &elem1, const invertedElemPrint &elem2)
              { return elem1.weight > elem2.weight; });

    // 4.[构建]根据查找结果构建json串返回给用户
    Json::Value root;
    for (auto &item : invertedList)
    {
        docInfo *doc = index->getForwardIndex(item.docId);
        if (nullptr == doc)
        {
            continue;
        }
        Json::Value elem;
        elem["title"] = doc->title;
        elem["desc"] = getDesc(doc->content, item.words[0]);
        elem["url"] = doc->url;
        elem["weight"] = item.weight;
        root.append(elem);
    }
    Json::FastWriter writer;
    *jsonString = writer.write(root);
}

// 根据文档内容和关键词，获取文件内容摘要
// 找到html中关键字第一次出现的位置，往前找50字节（不够从开头开始），往后找100字节（不够截至到结尾）
std::string Searcher::getDesc(const std::string &content, const std::string &keyword)
{
    const std::size_t prevStep = 50;
    const std::size_t nextStep = 100;
    // 1.找到首次出现的位置
    // std::size_t pos = content.find(keyword);
    auto iter = std::search(content.begin(), content.end(), keyword.begin(), keyword.end(),
                            [](char ch1, char ch2)
                            { return std::tolower(ch1) == std::tolower(ch2); });
    // 没有找到返回None --> 不可能出现，因为按照关键字创建的倒排拉链，不可能不出现该关键字
    if (iter == content.end())
    {
        return "None";
    }

    // 2.获取start和end;
    std::size_t pos = std::distance(content.begin(), iter);
    std::size_t start = 0;
    std::size_t end = content.size() - 1;
    if (pos > start + prevStep)
    {
        start = pos - prevStep;
    }
    if (pos + keyword.size() + nextStep < end)
    {
        end = pos + keyword.size() + nextStep;
    }
    // 3.截取子串
    if (start >= end)
    {
        return "None1";
    }
    return content.substr(start, end - start + 1);
}
