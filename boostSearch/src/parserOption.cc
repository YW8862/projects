#include "../include/parserOption.h"

//const &:输入参数
//*:输出参数
//&输入输出参数

bool enumFiles(const std::string &srcPath, std::vector<std::string> *filesList)
{
    namespace fs = boost::filesystem;
    fs::path rootPath(srcPath);
    if (!fs::exists(rootPath))
    {
        std::cerr << srcPath << " not exists" << std::endl;
        return false;
    }
    //定义一个空的迭代器，用于进行判断接待结果
    fs::recursive_directory_iterator end;
    // std::cout << "111111" << std::endl;
    // std::cout<<getcwd(nullptr,0)<<std::endl;
    for (fs::recursive_directory_iterator iter(rootPath); iter != end; iter++)
    {
        //如果不是常规文件，则忽略该文件
        if (!fs::is_regular_file(*iter))
        {
            continue;
        }
        //如果文件不以.html结尾，忽略
        if (iter->path().extension() != ".html")
        {
            continue;
        }
        std::cout << "debug: " << iter->path().string() << std::endl;
        //文件一定是合法的文件
        filesList->push_back(iter->path().string());
    }
    return true;
}

bool parseHtml(const std::vector<std::string> &filesList, std::vector<docInfo_t> *results)
{
    return true;
}

bool save(const std::vector<docInfo_t> &results, const std::string &rawPath)
{
    return true;
}