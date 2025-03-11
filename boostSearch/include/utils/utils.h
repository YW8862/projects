#ifndef __READFILE_H__
#define __READFILE_H__
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <boost/algorithm/string.hpp>

namespace ns_utils
{
    class FileUtils
    {
    public:
        static bool readFile(const std::string &filePath,std::string *result);
    };

    class StringUtils
    {
    public:
        static void cutString(const std::string &target,std::vector<std::string> *outString,const std::string &sep);
    };
};



#endif