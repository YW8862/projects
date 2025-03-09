#include "../include/parserOption.h"

int main()
{
    std::cout<<__FILE__<<": "<<getcwd(nullptr,0)<<std::endl;
    //1.递归式罗列每个文件名保存至filesList,方便后期进行一个一个文件的读取
    std::vector<std::string> filesList;
    if (!enumFiles(srcPath, &filesList))
    {
        std::cerr << "enum file name error !" << std::endl;
        return ENUMFILE;
    }

    //2.按照filesList读取每个文件的内容，并进行解析
    std::vector<docInfo_t> results;
    if (!parseHtml(filesList, &results))
    {
        std::cerr << "parser html error" << std::endl;
        return PARSERERROR;
    }

    //3.把解析完毕的文件内容写入到raw.txt当中，按照'\3'作为每个文档的分隔符
    if (!save(results, rawPath))
    {
        std::cerr << "save error" << std::endl;
        return SAVEERROR;
    }

    return 0;
}