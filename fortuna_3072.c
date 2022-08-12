#include "fortuna_3072.h"

#include <memory.h>

#include "chacha12.h"

// Generate random block
static inline void rand_block(F3072State* rng, uint8_t* out);
// Reseed the current state with entropy in reservoir
static inline void reseed_state(F3072State* rng);
// Increment a 384 bit buffer
static inline void increment_block(uint8_t* buf);

void f3072_random_fill(F3072State* rng, uint8_t* buf, uint64_t len) {
    if (rng && buf && len) {
        uint64_t rem_bytes = len % 48;
        for (uint64_t block = 0; block < len / 48; block++) {
            rand_block(rng, buf + block * 48);
            if (block % 65536 == 0) {
                reseed_state(rng);
            }
        }
        if (rem_bytes) {
            uint8_t rand_nums[48];
            rand_block(rng, rand_nums);
            memcpy(buf + len - rem_bytes, rand_nums, rem_bytes);
        }
        reseed_state(rng);
    }
}

void f3072_add_entropy(F3072State* rng, uint8_t* buf, uint64_t len) {
    if (rng && buf && len) {
        for (uint16_t i = 0; i < len; i++) {
            if (rng->mix % 48 == 0) {
                uint8_t* addr = rng->reservoir + rng->mix;
                chacha12(addr, addr);
            }
            rng->mix = (rng->mix + 1) % 3072;
            rng->reservoir[rng->mix] ^= buf[i];
        }
    }
}

// Verifying validity of rng and out is left to caller
static inline void rand_block(F3072State* rng, uint8_t* out) {
    increment_block(rng->rng_state);
    memcpy(out, rng->rng_state, 48);
    chacha12(out, out);
}

// Verifying validity of rng is left to caller
static inline void reseed_state(F3072State* rng) {
    uint64_t pool_id = (uint64_t)__builtin_ctzll(++rng->ctr);
    uint8_t* reseed_ptr = rng->reservoir + pool_id * 48;
    uint8_t reseed_block[48];
    memcpy(reseed_block, reseed_ptr, 48);
    increment_block(reseed_ptr);
    chacha12(reseed_block, reseed_block);
    for (uint64_t i = 0; i < 48; i++) {
        rng->rng_state[i] ^= reseed_block[i];
    }
}

// Verifying validity of buf is left to caller
static inline void increment_block(uint8_t* buf) {
    for (uint64_t i = 0; i < 48; i++) {
        if (++buf[i]) {
            return;
        }
    }
}
