#pragma once
#include <string>

class SHA256 {
public:
    static std::string Hash(const std::string& input);
};