#include <stdint.h>
#include <limits.h>

// Maximum Data Value
#define MAXVAL INT_MAX

/*	This function is an imported function: https://www.pcg-random.org/download.html
	This is a way better RNG than C's stock RNG which just sucks.
*/
typedef struct { uint64_t state;  uint64_t inc; } pcg32_random_t;
uint32_t pcg32_random_r(pcg32_random_t* rng) {
	// *Really* minimal PCG32 code / (c) 2014 M.E. O'Neill / pcg-random.org
	// Licensed under Apache License 2.0 (NO WARRANTY, etc. see website)
    uint64_t oldstate = rng->state;
    // Advance internal state
    rng->state = oldstate * 6364136223846793005ULL + (rng->inc|1);
    // Calculate output function (XSH RR), uses old state for max ILP
    uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
    uint32_t rot = oldstate >> 59u;
    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}

void GenerateData(int * arr, int size)
{
    int i;
    pcg32_random_t seed;
    srand((int) time(NULL));
    seed.state = rand() * rand() * rand() * rand();

    for(i = 0; i < size; i++)
    {
        arr[i] = (int) pcg32_random_r(&seed) % MAXVAL;
        if(arr[i] < 0) arr[i] *= -1;
    }
}
