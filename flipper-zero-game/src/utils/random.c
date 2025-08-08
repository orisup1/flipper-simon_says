#include <stdlib.h>
#include <time.h>
#include "random.h"

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