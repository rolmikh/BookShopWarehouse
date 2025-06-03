#include "HashAndSalt.h"
#include <random>
#include <string>

std::string HashAndSalt::CreateSalt(int size) {
    const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string salt;
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<> dist(0, chars.size() - 1);

    for (int i = 0; i < size; ++i)
        salt += chars[dist(rng)];

    return salt;
}

std::string HashAndSalt::GenerateHash(const std::string& password, const std::string& salt) {
    return SHA256::Hash(password + salt);
}

bool HashAndSalt::AreEqual(const std::string& plainText, const std::string& storedHash, const std::string& salt) {
    return GenerateHash(plainText, salt) == storedHash;
}