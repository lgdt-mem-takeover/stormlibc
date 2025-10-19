#include <storm/storm.h>

#define MAX_THREADS 12
#include <stdint.h>
#include <time.h>

static uint64_t s[4]; // PRNG state

static inline uint64_t rotl(const uint64_t x, int k) {
    return (x << k) | (x >> (64 - k));
}

static uint64_t splitmix64_state;

// Good seeding with splitmix64:
static uint64_t splitmix64(void) {
    uint64_t z = (splitmix64_state += 0x9e3779b97f4a7c15);
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
    z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
    return z ^ (z >> 31);
}

void dice_init(void) {
    splitmix64_state = (uint64_t)time(NULL);
    for (int i = 0; i < 4; ++i)
        s[i] = splitmix64();
}

uint64_t next(void) {
    const uint64_t result = rotl(s[1] * 5, 7) * 9;
    const uint64_t t = s[1] << 17;
    s[2] ^= s[0];
    s[3] ^= s[1];
    s[1] ^= s[2];
    s[0] ^= s[3];
    s[2] ^= t;
    s[3] = rotl(s[3], 45);
    return result;
}

uint64_t dice_roll(uint64_t n, uint64_t m) {
    uint64_t accum = 0;
    for(uint64_t i = 0; i < n; i++)
        accum += 1 + (next() % m);
    return accum;
}

