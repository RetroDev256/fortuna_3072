#ifndef FORTUNA_768_H_INCLUDED
#define FORTUNA_768_H_INCLUDED

#include <stdint.h>

typedef struct f768State_struct {
    uint8_t reservoir[768];  // Entropy pools to reseed from
    uint8_t rng_state[48];  // Current state of the CSPRNG
    uint64_t mix;  // Current mixing address for new entropy
    uint64_t ctr;  // Times the CSPRNG has been reseeded
} F768State;

// Tips:
// Set mix and ctr to 0 on initialization
// Add entropy before using
// Save reservoir on program exit,
//     restore from file on program load

// Fill buffer with random numbers
void f768_random_fill(F768State* state, uint8_t* buf, uint64_t len);
// Add entropy to the reservoir
void f768_add_entropy(F768State* state, uint8_t* buf, uint64_t len);

#endif
