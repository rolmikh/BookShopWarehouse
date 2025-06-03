#include "HashAndSalt.h"
#include "base64.h"
#include <windows.h>
#include <sstream>
#include <iomanip>
#include <random>
#include <algorithm>
#include <vector>
#include <string>

std::string HashAndSalt::CreateSalt(int size) {
    std::vector<uint8_t> salt(size);
    HCRYPTPROV hCryptProv;
    CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_MACHINE_DEFAULT);
    CryptGenRandom(hCryptProv, size, salt.data());
    CryptReleaseContext(hCryptProv, 0);
    return Base64::Encode(salt);
}

std::string HashAndSalt::GenerateHash(const std::string& input, const std::string& salt) {
    std::string combined = input + salt;
    std::vector<uint8_t> data(combined.begin(), combined.end());

    HCRYPTPROV hCryptProv;
    HCRYPTHASH hHash;
    CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_MACHINE_DEFAULT);
    CryptCreateHash(hCryptProv, CALG_SHA_256, 0, 0, &hHash);
    CryptHashData(hHash, data.data(), data.size(), 0);

    DWORD hashLen = 32;
    std::vector<uint8_t> hash(hashLen);
    CryptGetHashParam(hHash, HP_HASHVAL, hash.data(), &hashLen, 0);

    CryptDestroyHash(hHash);
    CryptReleaseContext(hCryptProv, 0);

    return Base64::Encode(hash);
}

bool HashAndSalt::AreEqual(const std::string& plainTextInput, const std::string& hashedInput, const std::string& salt) {
    std::string newHashed = GenerateHash(plainTextInput, salt);
    return newHashed == hashedInput;
}

std::string HashAndSalt::GenerateToken(int length) {
    const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> dist(0, chars.size() - 1);

    std::string token;
    for (int i = 0; i < length; ++i)
        token += chars[dist(generator)];
    return token;
}