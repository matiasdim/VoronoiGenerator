#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: seedsFileName seedsNumber width height");
        exit(1);
    }

    char *seedsFileName = argv[1];
    int SEEDS_NUMBER = atoi(argv[2]);
    int M = atoi(argv[3]);
    int N = atoi(argv[4]);
    int arraySize = M * N;
    int voronoi[arraySize]; // init

    time_t t;
    int i;
    int j;
    int k;
    int seeds[SEEDS_NUMBER];

    FILE *seedsFile = fopen(seedsFileName, "r");
    if (seedsFile == NULL) {
        printf("Could not open file %s", seedsFileName);
        exit(1);
    }

    int readSeed;
    for (i = 0; i < SEEDS_NUMBER; i++) {
        fscanf(seedsFile, "%d", &readSeed);
        seeds[i] = readSeed;
    }

    for(i= 0; i < arraySize; i++){
        voronoi[i] = 0;
    }

    for(i= 0; i < SEEDS_NUMBER; i++){
        voronoi[seeds[i]] = -1;
    }


    double currentDistance = 0;
    double minDistance;
    int belongingSeed;
    //Timing
    struct timeval start, end;
    double elapsedTime;
    gettimeofday(&start, NULL);
    for(i= 0; i< arraySize; i++){
        minDistance = INFINITY;
        if(voronoi[i] != -1) {
            int voronoiI = i / N;
            int voronoiJ = i % N;
            for (j = 0; j < SEEDS_NUMBER; j++) {
                int candidateSeed = seeds[j];
                int seedI = candidateSeed/ N;
                int seedJ = candidateSeed % N;
                currentDistance = sqrt(
                        pow((seedI - voronoiI), 2) +
                        pow((seedJ - voronoiJ), 2)
                        );
                if (currentDistance < minDistance) {
                    minDistance = currentDistance;
                    belongingSeed = j;
                }
            }
            voronoi[i] = belongingSeed;
        }
    }

    gettimeofday(&end, NULL);
    elapsedTime = (end.tv_sec - start.tv_sec) * 1000.0;
    elapsedTime += (end.tv_usec - start.tv_usec) / 1000.0;
    fprintf(stderr, "Elapsed %f\n ", elapsedTime);
    for (i = 0; i < arraySize; i++) {
        if (i > 0 && i % N == 0) {
            printf("\n");
        }
        printf("%d ", voronoi[i]);
    }
    return 0;
}