#ifndef __READFILE_H__
#define __READFILE_H__
#include <iostream>
#include <string>
#include <fstream>

namespace ns_utils
{
    class FileUtils
    {
    public:
        static bool readFile(const std::string &filePath,std::string *result);
    };
};



#endif