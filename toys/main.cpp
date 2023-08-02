#include <cstdio>
#include <iostream>
#include "nlohmann/json.hpp"

int main(int, char**)
{
    std::printf("Hello world!\n");
    auto j = nlohmann::json::parse(R"({"happy": true, "pi": 3.141})");
    std::cout << j.dump(4) << std::endl;
    return 0;
}
