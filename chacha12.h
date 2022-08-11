#ifndef CHACHA12_H_INCLUDED
#define CHACHA12_H_INCLUDED

#include <stdint.h>

// Hash 384 bit block (Thread Safe)
// Input: 48 bytes, Output: 48 bytes
void chacha12(const uint8_t* in, uint8_t* out);

#endif
