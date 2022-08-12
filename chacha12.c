#include "chacha12.h"

#include <memory.h>

// ChaCha quarter mixing and rotation
#define ROTL(a, b) (((a) << (b)) | ((a) >> (32 - (b))))
#define QR(a, b, c, d) \
    (a += b, \
     d ^= a, \
     d = ROTL(d, 16), \
     c += d, \
     b ^= c, \
     b = ROTL(b, 12), \
     a += b, \
     d ^= a, \
     d = ROTL(d, 8), \
     c += d, \
     b ^= c, \
     b = ROTL(b, 7))

void chacha12(const uint8_t* in, uint8_t* out) {
    if (in && out) {  // Verify in & out pointers
        uint32_t x[16];
        x[0] = 0x61707865U;  // expa
        x[1] = 0x3320646eU;  // nd 3
        x[2] = 0x79622d32U;  // 2 by
        x[3] = 0x6b206574U;  // te k
        memcpy(&x[4], in, 48);  // Initialize x to input
        for (uint64_t r = 0; r < 6; r++) {
            QR(x[0], x[4], x[8], x[12]);
            QR(x[1], x[5], x[9], x[13]);
            QR(x[2], x[6], x[10], x[14]);
            QR(x[3], x[7], x[11], x[15]);
            QR(x[0], x[5], x[10], x[15]);
            QR(x[1], x[6], x[11], x[12]);
            QR(x[2], x[7], x[8], x[13]);
            QR(x[3], x[4], x[9], x[14]);
        }
        // Combine original input and output
        for (uint64_t i = 0; i < 48; i++) {
            out[i] = ((uint8_t*)x)[i] + in[i];
        }
    }
}
