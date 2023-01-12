// Copyright (c) 2023 Fernando Pelliccioni.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <cstdint>

// #define Ch(x, y, z)  ((x & (y ^ z)) ^ z)
// #define Maj(x, y, z) ((x & (y | z)) | (y & z))
// #define SHR(x, n)    (x >> n)
// #define ROTR(x, n)   ((x >> n) | (x << (32 - n)))
// #define S0(x)        (ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22))
// #define S1(x)        (ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25))
// #define s0(x)        (ROTR(x, 7) ^ ROTR(x, 18) ^ SHR(x, 3))
// #define s1(x)        (ROTR(x, 17) ^ ROTR(x, 19) ^ SHR(x, 10))


inline uint32_t sigma0(uint32_t x) {
    return (x >> 7 | x << 25) ^ (x >> 18 | x << 14) ^ (x >> 3);
}
inline uint32_t sigma1(uint32_t x) {
    return (x >> 17 | x << 15) ^ (x >> 19 | x << 13) ^ (x >> 10);
}

namespace {

template <uint32_t N>
inline constexpr
uint32_t ROTR(uint32_t x) {
    return (x >> N) | (x << (32 - N));
}

inline constexpr
uint32_t s0(uint32_t x) {
    return ROTR<7>(x) ^ ROTR<18>(x) ^ (x >> 3);
}

inline constexpr
uint32_t s1(uint32_t x) {
    return ROTR<17>(x) ^ ROTR<19>(x) ^ (x >> 10);
}

// #define s0(x)        (ROTR(x, 7) ^ ROTR(x, 18) ^ SHR(x, 3))
// #define s1(x)        (ROTR(x, 17) ^ ROTR(x, 19) ^ SHR(x, 10))

} // anonymous namespace

