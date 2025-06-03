#pragma once
#include <string>
#include "Sha256.h"

class HashAndSalt {
public:
    static std::string CreateSalt(int size = 16);
    static std::string GenerateHash(const std::string& password, const std::string& salt);
    static bool AreEqual(const std::string& plainText, const std::string& storedHash, const std::string& salt);
};