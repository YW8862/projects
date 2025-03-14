#include "../include/searcher.h"
#include <cstdio>
#include <cstring>
int main()
{   
    //for test
    ns_searcher::Searcher *searcher = new ns_searcher::Searcher();
    searcher->initSearcher(rawPath);
    
    std::string query;
    std::string jsonString;
    while(true)
    {
        std::cout<<"input your query# ";
        char buffer[1024];
        fgets(buffer,sizeof(buffer)-1,stdin);
        buffer[strlen(buffer) - 1]=  '\0';
        query = buffer;
        searcher->search(query,&jsonString);
        std::cout<<jsonString<<std::endl;
    }
    return 0;
}