#include "../../include/utils/index.h"

using namespace ns_index;

ns_index::index *index::instance = nullptr;
std::mutex index::gmutex;
// 获取单例
ns_index::index *index::getInstance()
{
    if (nullptr == instance)
    {
        std::lock_guard<std::mutex> lockGuard(gmutex);
        if (nullptr == instance)
        {
            instance = new index();
        }
    }
    return instance;
}

// 建立正排索引和倒排索引
bool index::buildIndex(const std::string &rawFilePath)
{
    std::ifstream in(rawFilePath, std::ios::in | std::ios::binary);
    if (!in.is_open())
    {
        std::cerr << "raw file open error" << std::endl;
        return false;
    }
    std::string line;
    int cnt = 0;
    while (std::getline(in, line))
    {
        // 提取文档的内容，放到正排索引当中
        docInfo *doc = buildForwardIndex(line);
        if (doc == nullptr)
        {
            std::cerr << "build ForwardIndex fail: " << line << std::endl;
            continue;
        }
        // 根据提取的内容，提取关键字并且建立倒排索引
        if (!buildInvertedIndex(*doc))
        {
            continue;
        }
        cnt++;
        printf("\rbuild Index %4d...",cnt);
    }
    std::cout<<std::endl;
    return true;
}

//@doc:传入读入的一行文档内容
//@return value:建立正排索引后的文档结构体
docInfo *index::buildForwardIndex(const std::string &line)
{
    // 1.解析line,拆分字符串
    // line -> title,content,url
    std::vector<std::string> results;
    ns_utils::StringUtils::cutString(line, &results, SEP);
    // 如果拆分失败，直接返回nullptr
    if (results.size() != 3)
    {
        return nullptr;
    }
    // 2.根据拆分的字符串填充docinfo
    docInfo doc;
    doc.title = results[0];          // title
    doc.content = results[1];        // content
    doc.url = results[2];            // url
    doc.docId = forwardIndex.size(); // docID
    // 3.插入到正排索引当中
    forwardIndex.emplace_back(std::move(doc));
    return &forwardIndex.back();
}

//@doc:传入正排索引提取的文件内容 --> 根据提取的内容，提取关键字并且建立倒排索引
bool index::buildInvertedIndex(const docInfo &doc)
{
    // 1.分析文档，提取关键词 --> jieba分词
    class wordCnt
    {
    public:
        wordCnt() : titleCnt(0), contentCnt(0) {}
        int titleCnt;
        int contentCnt;
    };

    // 暂存词频映射表
    std::unordered_map<std::string, wordCnt> wordMap;
    // 对标题进行分词并且词频统计
    std::vector<std::string> titleWords;
    ns_utils::JiebaUtils::split(doc.title, &titleWords);
    for (std::string keyword : titleWords)
    {
        boost::to_lower(keyword);
        wordMap[keyword].titleCnt++;
    }

    // 将文档内容进行分词并且词频统计
    std::vector<std::string> contenWords;
    ns_utils::JiebaUtils::split(doc.content, &contenWords);
    for (std::string keyword : contenWords)
    {
        boost::to_lower(keyword);
        wordMap[keyword].contentCnt++;
    }
    
    // 填充倒排拉链
    for (auto &wordPair : wordMap)
    {
        invertedElem elem;
        elem.docId = doc.docId;                                                       // 填充倒排id
        elem.keyWord = wordPair.first;                                                // 填充倒排关键词
        elem.weight = 10 * wordPair.second.titleCnt + 1 * wordPair.second.contentCnt; // 填充关键词权重

        // 获取映射的倒排拉链
        invertedList_t &invertedList = invertedIndex[wordPair.first];
        invertedList.push_back(std::move(elem));
    }
    return true;
}

// 根据docID获得文档内容
docInfo *index::getForwardIndex(const uint64_t &docID)
{
    if (docID >= forwardIndex.size())
    {
        std::cerr << "docID error,invalid" << std::endl;
        return nullptr;
    }

    return &forwardIndex[docID];
}

// 根据关键字获取倒排拉链
invertedList_t *index::getInvertedList(const std::string &keyWord)
{
    auto iter = invertedIndex.find(keyWord);
    // 没有找到，直接返回
    if (iter == invertedIndex.end())
    {
        std::cerr << "not found invertedList by keyWord:" << keyWord << std::endl;
        return nullptr;
    }

    // 返回找到的倒排拉链
    return &(iter->second);
}
