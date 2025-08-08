#include "random.h"

#ifdef DESKTOP
#include <stdlib.h>
#include <time.h>

void init_random() {
    srand((unsigned int)time(NULL));
}

int get_random_number(int min, int max) {
    if(max < min) {
        int tmp = min; min = max; max = tmp;
    }
    int range = max - min + 1;
    return (rand() % range) + min;
}
#else
#include <furi_hal.h>

void init_random() {
    // No explicit seeding needed when using hardware RNG
}

int get_random_number(int min, int max) {
    if(max < min) {
        int tmp = min; min = max; max = tmp;
    }
    uint32_t r = furi_hal_random_get();
    uint32_t range = (uint32_t)(max - min + 1);
    return min + (int)(r % range);
}
#endif