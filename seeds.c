#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main (int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: seeds width height");
        exit(1);
    }

    int numberOfSeeds = atoi(argv[1]);
    int width = atoi(argv[2]);
    int height = atoi(argv[3]);

    int max = width * height;
    time_t t;
    srand((unsigned) time(&t));

    int i;
    for (i = 0; i < numberOfSeeds; i++) {
        int randomSeed = (rand() % max);
        printf("%d", randomSeed);
        if (i != numberOfSeeds - 1) {
            printf("\n");
        }
    }
}
