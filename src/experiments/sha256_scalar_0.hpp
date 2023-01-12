// Copyright (c) 2023 Fernando Pelliccioni.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <array>
#include <cstdint>
#include <iostream>

// Initialize array of round constants:
// (first 32 bits of the fractional parts of the cube roots of the first 64 primes 2..311):
const std::array<std::uint32_t, 64> K = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
    0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
    0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
    0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
    0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
    0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

// Initial hash values
// (first 32 bits of the fractional parts of the square roots of the first 8 primes 2..19):
const std::array<std::uint32_t, 8> H = {
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
};

std::array<std::uint32_t, 8> sha256(const std::vector<std::uint8_t> &message) {
    std::array<std::uint32_t, 8> hash = H;
    std::array<std::uint32_t, 64> w;

    std::size_t message_length = message.size();

    // Process the message in successive 512-bit chunks
    for (std::size_t i = 0; i < message_length; i += 64) {
        // Create a 64-entry message schedule array
        std::fill(w.begin(), w.end(), 0);
        for (std::size_t j = 0; j < 16; ++j) {
            std::size_t pos = i + j * 4;
            w[j] =  (std::uint32_t) message[pos    ] << 24 |
                    (std::uint32_t) message[pos + 1] << 16 |
                    (std::uint32_t) message[pos + 2] << 8  |
                    (std::uint32_t) message[pos + 3];
        }
        // Extend the first 16 words into the remaining 48 words
        for (std::size_t j = 16; j < 64; ++j) {
            std::uint32_t s0 = (w[j - 15] >> 7 | w[j - 15] << 25) ^
                               (w[j - 15] >> 18 | w[j - 15] << 14) ^ (w[j - 15] >> 3);
            std::uint32_t s1 = (w[j - 2] >> 17 | w[j - 2] << 15) ^
                               (w[j - 2] >> 19 | w[j - 2] << 13) ^ (w[j - 2] >> 10);
            w[j] = w[j - 16] + s0 + w[j - 7] + s1;
        }
        // Initialize working variables
        std::uint32_t a = hash[0];
        std::uint32_t b = hash[1];
        std::uint32_t c = hash[2];
        std::uint32_t d = hash[3];
        std::uint32_t e = hash[4];
        std::uint32_t f = hash[5];
        std::uint32_t g = hash[6];
        std::uint32_t h = hash[7];
        // Compression function main loop
        for (std::size_t j = 0; j < 64; ++j) {
            std::uint32_t s1 = (e >> 6 | e << 26) ^ (e >> 11 | e << 21) ^ (e >> 25 | e << 7);
            std::uint32_t ch = (e & f) ^ (~e & g);
            std::uint32_t temp1 = h + s1 + ch + K[j] + w[j];
            std::uint32_t s0 = (a >> 2 | a << 30) ^ (a >> 13 | a << 19) ^ (a >> 22 | a << 10);
            std::uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
            std::uint32_t temp2 = s0 + maj;
            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }
        // Add the compressed chunk to the current hash value
        hash[0] += a;
        hash[1] += b;
        hash[2] += c;
        hash[3] += d;
        hash[4] += e;
        hash[5] += f;
        hash[6] += g;
        hash[7] += h;
    }
    return hash;
}



/*

Note that this implementation is a basic version of the SHA-256 algorithm and can be improved by
adding support for handling messages whose length is greater than 2^64 bits and also padding,
handle endianess and added more options for output format for the final digest. it's also important to note
that you should use it only for educational or testing purposes only and not for any kind of production use.
*/
