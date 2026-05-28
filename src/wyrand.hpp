#pragma once

#include <cstdint> // Required for uint64_t
#include <limits>  // Required for std::numeric_limits

// Required for Windows/MSVC compiler 128-bit math
#ifdef _MSC_VER
#include <intrin.h>
#endif

namespace Wyrand {

class Wyrand {
private:
    uint64_t state;

public:
    using result_type = uint64_t; // Required type definition for C++ URBG compatibility

    explicit Wyrand(uint64_t seed = 0) : state(seed) {}

    void seed(uint64_t seed) {
        state = seed;
    }

    static constexpr result_type min() { return 0; }
    static constexpr result_type max() { return std::numeric_limits<result_type>::max(); }

    result_type operator()() {
        state += 0xa0761d6478bd642fULL;


#ifdef _MSC_VER
#if defined(_M_X64) || defined(_M_ARM64)
        // Windows / MSVC 64-bit implementation
        uint64_t high;
        uint64_t low = _umul128(state, state ^ 0xe7037ed1a0b428dbULL, &high);
        return high ^ low;
#else
        // Windows / MSVC 32-bit (x86) fallback implementation
        uint64_t u = state;
        uint64_t v = state ^ 0xe7037ed1a0b428dbULL;
        uint64_t u_lo = u & 0xffffffffULL;
        uint64_t u_hi = u >> 32;
        uint64_t v_lo = v & 0xffffffffULL;
        uint64_t v_hi = v >> 32;

        uint64_t t = u_lo * v_lo;
        uint64_t w0 = t & 0xffffffffULL;
        uint64_t k = t >> 32;

        t = u_hi * v_lo + k;
        uint64_t w1 = t & 0xffffffffULL;
        uint64_t w2 = t >> 32;

        t = u_lo * v_hi + w1;
        uint64_t low = (t << 32) | w0;
        uint64_t k2 = t >> 32;

        uint64_t high = u_hi * v_hi + w2 + k2;
        return high ^ low;
#endif
#else
        // Linux / Mac / Android / iOS (GCC/Clang) implementation
        __uint128_t t = static_cast<__uint128_t>(state) * (state ^ 0xe7037ed1a0b428dbULL);
        return static_cast<result_type>(t >> 64) ^ static_cast<result_type>(t);
#endif
    }
};

}