#include "../include/searcher.h"

using namespace ns_searcher;

void Searcher::initSearcher(const std::string &rawFile)
{
    // 1.获取或者创建index对象
    index = ns_index::index::getInstance();
    // 2.根据index对象创建索引
    index->buildIndex(rawFile);
}

void Searcher::search(const std::string &query, std::string *jsonString)
{
    // 1.[分词]对query分词
    std::vector<std::string> words;
    ns_utils::JiebaUtils::extractWords(query, &words);
    // 2.[触发]根据分词后的各个词进行查找
    invertedList_t invertedList;
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
        invertedList.insert(invertedList.end(), list->begin(), list->end());
    }

    // 3.[合并排序]根据汇总的查找结果按照相关性进行降序排序
    std::sort(invertedList.begin(), invertedList.end(), [](const invertedElem &elem1, const invertedElem &elem2)
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
        elem["desc"] = doc->content;
        elem["url"] = doc->url;

        root.append(elem);
    }
    Json::StyledWriter writer;
    *jsonString = writer.write(root);
}