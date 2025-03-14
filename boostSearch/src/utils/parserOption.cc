#include "../../include/utils/parserOption.h"

//const &:输入参数
//*:    输出参数
//&:    输入输出参数

//遍历.html文件路径
bool enumFiles(const std::string &srcPath, std::vector<std::string> *filesList)
{
    namespace fs = boost::filesystem;
    fs::path rootPath(srcPath);
    //判断路径是否存在，如果不存在，则直接返回
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
        //判断文件名后缀是否符合要求
        if (iter->path().extension() != ".html")
        {
            continue;
        }
        std::cout << "debug: " << iter->path().string() << std::endl;
        //文件一定是合法的文件
        filesList->push_back(iter->path().string()); //将所有.html文件路径保存在filesList中，以便后续解析
    }
    return true;
}

bool parseTitle(const std::string &file, std::string *title)
{
    //查找title标签开始位置
    std::size_t begin = file.find("<title>");
    //如果未找到，直接返回false
    if (begin == std::string::npos)
    {
        return false;
    }
    //查找title标签结束位置
    std::size_t end = file.find("</title>");
    //如果未找到，直接返回false
    if (end == std::string::npos)
    {
        return false;
    }

    begin += std::string("<title>").size();

    if (begin > end)
    {
        return false;
    }
    *title = file.substr(begin, end - begin);

    return true;
}

bool parseContent(const std::string &file, std::string *content)
{
    //基于状态机去标签
    enum status
    {
        LABAL,
        CONTENT
    };

    enum status s = LABAL;

    for (auto c : file)
    {
        switch (s)
        {
        case LABAL:
            //如果是>字符，切换到内容态
            if (c == '>')
            {
                s = CONTENT;
            }
            break;
        case CONTENT:
            //如果是<字符，切换到标签态
            if (c == '<')
            {
                s = LABAL;
            }
            else
            {
                //不保留原来的回车\n符转为改为 ' '
                if (c == '\n')
                {
                    c = ' ';
                }
                *content += c;
            }
        default:
            break;
        }
    }
    return true;
}

bool parseUrl(const std::string &file, std::string *url)
{
    //获取url头
    std::string urlHead = "https://www.boost.org/doc/libs/1_87_0/doc/html";
    std::string urlTail = file.substr(srcPath.size());
    //获取文件url尾
    *url = urlHead + urlTail;
    return true;
}

void showDoc(const docInfo_t &doc)
{
    std::cout << "title: " << doc.title << " url: " << doc.url << std::endl;
    //sleep(1);
}

//解析文件内容
//@const std::vector<std::string> &filesList: 所有html的文件路径
//std::vector<docInfo_t> *results： 所有文件的信息（标题，内容，url）
bool parseHtml(const std::vector<std::string> &filesList, std::vector<docInfo_t> *results)
{
    for (const std::string &file : filesList)
    {
        //1.读取文件,read
        std::string result;
        ;
        //1.1如果该文件读取失败，直接忽略
        if (!ns_utils::FileUtils::readFile(file, &result))
        {
            continue;
        }
        //2.解析指定的文件,提取tittle
        docInfo_t doc;
        //2.1如果解释失败，直接忽略
        if (!parseTitle(result, &doc.title))
        {
            continue;
        }
        //3.解析指定的文件,提取contents --->去标签
        if (!parseContent(result, &doc.content))
        {
            continue;
        }
        //4.解析文件路径，构建url
        if (!parseUrl(file, &doc.url))
        {
            continue;
        }
        showDoc(doc);
        //完成所有解析任务
        results->emplace_back(std::move(doc));
    }
    return true;
}

//报错内容到文件当中
bool save(const std::vector<docInfo_t> &results, const std::string &rawPath)
{
    //使用二进制写入
    std::ofstream out(rawPath, std::ios::out | std::ios::binary);
    if (!out.is_open())
    {
        std::cerr << "open file " << rawPath << " fail" << std::endl;
    }

    //向文档中写入内容
    for (auto &result : results)
    {
        std::string outString;
        outString += result.title;
        outString += SEP;
        outString += result.content;
        outString += SEP;
        outString += result.url;
        outString += '\n';
        out.write(outString.c_str(),outString.size());
    }

    out.close();
    return true;
}