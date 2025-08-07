#include <stdlib.h>
#include <time.h>
#include "random.h"

void initialize_random() {
    srand(time(NULL));
}

int get_random_number(int min, int max) {
    return rand() % (max - min + 1) + min;
}