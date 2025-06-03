#pragma once
#include <string>
#include <vector>

class HashAndSalt {
public:
    std::string CreateSalt(int size);
    std::string GenerateHash(const std::string& input, const std::string& salt);
    bool AreEqual(const std::string& plainTextInput, const std::string& hashedInput, const std::string& salt);
    std::string GenerateToken(int length);
};