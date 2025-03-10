#include "../../include/utils/readFile.h"

using namespace ns_utils;


bool FileUtils::readFile(const std::string &filePath,std::string *result)
{
    std::ifstream in(filePath,std::ios::in);
    if(!in.is_open())
    {
        std::cerr<<filePath<<" open fail"<<std::endl;
        return false;
    }
    std::string line;
    while(std::getline(in,line))
    {
        *result += line;
    }

    in.close();
    return true;
}
