#include "../thirdpart/cpp-httplib/httplib.h"
#include "../include/searcher.h"
#include "../include/utils/log.h"
#include <iostream>
#include <filesystem>
const std::string input = "data/raw_html/raw.txt";
const std::string root_path = "wwwroot";

int main()
{
    char buffer[1024];
    getcwd(buffer, sizeof(buffer) - 1);
    std::cout << "current work dir " << buffer << std::endl;

    ns_searcher::Searcher search;
    search.initSearcher(input);

    httplib::Server svr;
    svr.set_base_dir(root_path.c_str());
    svr.Get("/s", [&search](const httplib::Request &req, httplib::Response &rsp) {});

    LOG(NORMAL, "服务器启动成功...");
    svr.listen("0.0.0.0", 8888);
    return 0;
}