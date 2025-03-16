#include "../thirdpart/cpp-httplib/httplib.h"
#include "../include/searcher.h"
#include "../include/utils/log.h"
#include <iostream>
#include <filesystem>
const std::string input = "data/raw_html/raw.txt";
const std::string root_path = "wwwroot";

int main()
{
    //建立搜索模块
    ns_searcher::Searcher searcher;
    searcher.initSearcher(input);

    //创建服务模块
    httplib::Server svr;
    svr.set_base_dir(root_path);
    svr.Get("/s",[&searcher](const httplib::Request &request,httplib::Response &response)
        {
            if(!request.has_param("word"))
            {
                response.set_content("input keyword please","text/plain;charset = utf-8");
                return;
            }
            std::string word = request.get_param_value("word");
            std::cout<<"user input:"<<word<<std::endl;

            //获取搜索结果
            std::string jsonString;
            searcher.search(word,&jsonString);
            //返回搜索结果
            response.set_content(jsonString,"application/json");
        });
        svr.listen("0.0.0.0",8888);
    return 0;
}