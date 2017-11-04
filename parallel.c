#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

extern void voronoi(
        int *matrix,
        int *seeds,
        int numberOfSeeds,
        int width,
        int height);

int main (int argc, char *argv[])
{
    if (argc != 5) {
        printf ("Usage: seedsFileName seeds width height");
        exit(1);
    }

    int i;
    int j;
    time_t t;
    char *seedsFileName = argv[1];
    int numberOfSeeds = atoi(argv[2]);
    int height = atoi(argv[3]);
    int width = atoi(argv[4]);
    int arraySize = width * height;

    struct timeval start, end;
    double elapsedTime;

    srand((unsigned) time(&t));
    int seeds[numberOfSeeds];

    int *matrix = malloc(arraySize * sizeof(int));
    for (i = 0; i < arraySize; i++) {
        matrix[i] = 0;
    }

    FILE *seedsFile = fopen(seedsFileName, "r");
    if (seedsFile == NULL) {
        printf("Could not open file %s", seedsFileName);
        exit(1);
    }

    int readSeed;
    for (i = 0; i < numberOfSeeds; i++) {
        fscanf(seedsFile, "%d", &readSeed);
        seeds[i] = readSeed;
        matrix[readSeed] = -1;
    }

    gettimeofday(&start, NULL);
    voronoi(matrix, seeds, numberOfSeeds, width, height);
    gettimeofday(&end, NULL);

    for (i = 0; i < arraySize; i++) {
        if (i > 0 && i % width == 0) {
            printf("\n");
        }
        printf("%d ", matrix[i]);
    }

    elapsedTime = (end.tv_sec - start.tv_sec) * 1000.0;
    elapsedTime += (end.tv_usec - start.tv_usec) / 1000.0;

    fprintf(stderr, "Elapsed %f\n ", elapsedTime);
    free(matrix);
}
