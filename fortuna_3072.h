#ifndef FORTUNA_3072_H_INCLUDED
#define FORTUNA_3072_H_INCLUDED

#include <stdint.h>

typedef struct f3072State_struct {
    uint8_t reservoir[3072];  // Entropy pools to reseed from
    uint8_t rng_state[48];  // Current state of the CSPRNG
    uint64_t mix;  // Current mixing address for new entropy
    uint64_t ctr;  // Times the CSPRNG has been reseeded
} F3072State;

// Tips:
// Set mix and ctr to 0 on initialization
// Add entropy before using
// Save reservoir on program exit,
//     restore from file on program load

// Fill buffer with random numbers
void f3072_random_fill(F3072State* state, uint8_t* buf, uint64_t len);
// Add entropy to the reservoir
void f3072_add_entropy(F3072State* state, uint8_t* buf, uint64_t len);

#endif
