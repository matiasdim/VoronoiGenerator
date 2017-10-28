#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

typedef struct Tuple {
    int i;
    int j;
} Tuple;

bool numberInArray(int valI, int valJ, Tuple array[], int seedsNum){
    int i;
    for(i= 0; i<seedsNum; i++){
        if (valI == array[i].i && valJ == array[i].j){
            return true;
        }
    }
    return false;
}

int main(int argc, char *argv[]) {
    int SEEDS_NUMBER = atoi(argv[1]);
    int M = atoi(argv[2]);
    int N = atoi(argv[3]);
    int voronoi[M][N]; // init
    time_t t;
    int i;
    int j;
    int k;
    struct Tuple seed;

    // Random location for seeds
    srand((unsigned) time(&t));
    Tuple randomSeeds[SEEDS_NUMBER];
    for(i= 0; i<M; i++){
        for(j= 0; j<N; j++){
            voronoi[i][j] = 0;
        }
    }

    for(i= 0; i<SEEDS_NUMBER; i++){
        seed.i  = (rand() % M);
        seed.j =(rand() % N);
        if (!numberInArray(seed.i, seed.j, randomSeeds, SEEDS_NUMBER)){
            randomSeeds[i] = seed;
            voronoi[seed.i][seed.j] = -1;
        }else{
            i--;
        }
    }


    double currentDistance = 0;
    double minDistance;
    int belongingSeed;
    //Timing
    struct timeval start, end;
    double elapsedTime;
    gettimeofday(&start, NULL);
    for(i= 0; i<M; i++){
        for(j= 0; j<N; j++){
            minDistance = INFINITY;
            if(voronoi[i][j] != -1) {
                for (k = 0; k < SEEDS_NUMBER; k++) {
                    currentDistance = sqrt(pow((randomSeeds[k].i - i), 2) + pow((randomSeeds[k].j - j), 2));
                    if (currentDistance < minDistance) {
                        minDistance = currentDistance;
                        belongingSeed = k;
                    }
                }
                voronoi[i][j] = belongingSeed;
            }
        }
    }
    gettimeofday(&end, NULL);
    elapsedTime = (end.tv_sec - start.tv_sec) * 1000.0;
    elapsedTime += (end.tv_usec - start.tv_usec) / 1000.0;
    fprintf(stderr, "Elapsed %f\n ", elapsedTime);
    for(i= 0; i<M; i++){
        for(j= 0; j<N; j++){
            printf("%d ", voronoi[i][j]);
        }
        printf("\n");
    }
    return 0;
}