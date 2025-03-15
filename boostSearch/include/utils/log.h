#include <iostream>
#include <string>
#include <ctime>
#define LOG(LEVEL, MESSAGE) log(#LEVEL, MESSAGE, __FILE__, __LINE__)

enum
{
    NORMAL = 1,
    WARNING,
    DEBUG,
    FATAL
};

void log(std::string level, std::string message, std::string file, int line);
