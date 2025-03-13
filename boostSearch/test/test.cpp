#include <iostream>
#include <string>
#include <vector>
#include <jsoncpp/json/json.h>

int main()
{
    Json::Value root;
    Json::Value item1;
    item1["key1"] = "value1";
    item1["key2"] = "value2";

    Json::Value item2;
    item2["key1"] = "value1";
    item2["key2"] = "value2";

    root.append(item1);
    root.append(item2);
    Json::StyledWriter writer;
    std::string s = writer.write(root);

    std::cout<<s<<std::endl;
    return 0;
}

