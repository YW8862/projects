#include "../include/searcher.h"

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
        std::cin>>query;
        searcher->search(query,&jsonString);
        std::cout<<jsonString<<std::endl;
    }
    return 0;
}