#pragma once 

#include <nlohmann/json.hpp>
#include <fstream>

namespace tools
{
    inline nlohmann::json loadJson(const char *path)
    {
        std::ifstream f(path);
        return nlohmann::json::parse(f);
    }
}