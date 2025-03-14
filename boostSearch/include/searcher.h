#ifndef __SEARCHER_H__
#define __SEARCHER_H__
#include "algorithm"
#include "jsoncpp/json/json.h"
#include "utils/index.h"

namespace ns_searcher
{
    class Searcher
    {
    public:
        Searcher()
        {
        }

        ~Searcher()
        {
        }
        // 初始化引擎
        
        void initSearcher(const std::string &rawFile);

        // 查找
        //@query:搜索关键字
        //@jsonString:返回给用户(搜索结果)

        void search(const std::string &query, std::string *jsonString);

        std::string getDesc(const std::string &content,const std::string &keyword);

    private:
        ns_index::index *index;
    };
};

#endif
