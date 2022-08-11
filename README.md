# fortuna_768
Custom Implementation of a Fortuna CSPRNG Varient

Know what /dev/random is? Well this is basically that same level of CSPRNG.
Except with a much larger state, and around the same speed. (~320 MiB/s one thread on my machine)
It uses 12 rounds of ChaCha for mixing, and has 64 pools in it's reservoir.

Enjoy :)
