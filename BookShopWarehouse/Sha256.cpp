#include "sha256.h"
#include <array>
#include <cstdint>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

namespace {
    constexpr uint32_t K[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
        0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
        0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
        0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf6e0acf,
        0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
        0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
        0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
        0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
        0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };

    inline uint32_t Ch(uint32_t x, uint32_t y, uint32_t z) { return (x & y) ^ (~x & z); }
    inline uint32_t Maj(uint32_t x, uint32_t y, uint32_t z) { return (x & y) ^ (x & z) ^ (y & z); }
    inline uint32_t Sigma0(uint32_t x) { return (x >> 2) ^ (x >> 13) ^ (x >> 22); }
    inline uint32_t Sigma1(uint32_t x) { return (x >> 6) ^ (x >> 11) ^ (x >> 25); }
    inline uint32_t sigma0(uint32_t x) { return (x >> 7) ^ (x >> 18) ^ (x << 29); } // битовый сдвиг влево
    inline uint32_t sigma1(uint32_t x) { return (x >> 17) ^ (x >> 19) ^ (x << 27); }

    constexpr std::array<uint32_t, 8> H = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };
}

std::string SHA256::Hash(const std::string& input) {
    std::string padded = input;
    padded += '\x80';

    size_t padLen = 64 - ((input.size() + 9) % 64);
    padded += std::string(padLen, '\x00');

    uint64_t bitLen = input.size() * 8;
    for (int i = 0; i < 8; ++i) {
        padded += static_cast<char>((bitLen >> (56 - i * 8)) & 0xFF);
    }

    std::array<uint32_t, 8> state = H;

    const int blockCount = padded.size() / 64;

    for (int i = 0; i < blockCount; ++i) {
        std::array<uint32_t, 64> w{};

        for (int j = 0; j < 16; ++j) {
            w[j] = (static_cast<uint32_t>(padded[i * 64 + j * 4]) << 24) |
                (static_cast<uint32_t>(padded[i * 64 + j * 4 + 1]) << 16) |
                (static_cast<uint32_t>(padded[i * 64 + j * 4 + 2]) << 8) |
                static_cast<uint32_t>(padded[i * 64 + j * 4 + 3]);
        }

        for (int j = 16; j < 64; ++j) {
            w[j] = sigma1(w[j - 2]) + w[j - 7] + sigma0(w[j - 15]) + w[j - 16];
        }

        std::array<uint32_t, 8> work = state;

        for (int j = 0; j < 64; ++j) {
            uint32_t t1 = work[7] + Sigma1(work[4]) + Ch(work[4], work[5], work[6]) + K[j] + w[j];
            uint32_t t2 = Sigma0(work[0]) + Maj(work[0], work[1], work[2]);

            work[7] = work[6];
            work[6] = work[5];
            work[5] = work[4];
            work[4] = work[3] + t1;
            work[3] = work[2];
            work[2] = work[1];
            work[1] = work[0];
            work[0] = t1 + t2;
        }

        for (int j = 0; j < 8; ++j) {
            state[j] += work[j];
        }
    }

    std::stringstream ss;
    for (const auto& val : state) {
        ss << std::hex << std::setw(8) << std::setfill('0') << val;
    }

    return ss.str();
}