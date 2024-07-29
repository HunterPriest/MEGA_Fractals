#pragma once 

#include <nlohmann/json.hpp>

namespace tools
{
    nlohmann::json loadJson(const char *path)
    {
        std::fstream f("Configs/Graphics.json");
        return nlohmann::json::parse(f);
    }
}