#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
 
#define N 5 // matrix width
#define M 5 // matrix height
#define SEEDS_NUMBER 2 // matrix height
// pending to figure out how to define the size with the above constants
int voronoi[M][N]; // init

typedef struct Tuple {
    int i;
    int j;
} Tuple;

bool numberInArray(int valI, int valJ, Tuple array[]){
    int i;
    for(i= 0; i<SEEDS_NUMBER; i++){
        if (valI == array[i].i && valJ == array[i].j){
            return true;
        }
    }
    return false;
}

int main() {
    time_t t;

    int i;
    int j;
    int k;

    struct Tuple seed;

    // Random location for seeds
    srand((unsigned) time(&t));
    Tuple randomSeeds[SEEDS_NUMBER] = {(0,0)};
    for(i= 0; i<SEEDS_NUMBER; i++){
        seed.i  = (rand() % M);
        seed.j =(rand() % N);
        if (!numberInArray(seed.i, seed.j, randomSeeds)){
            randomSeeds[i] = seed;
            voronoi[seed.i][seed.j] = -1;
        }else{
            i--;
        }
    }

    double currentDistance = 0;
    double minDistance;
    int belongingSeed;
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

    for(i= 0; i<M; i++){
        for(j= 0; j<N; j++){
            printf("%d \t", voronoi[i][j]);
        }
        printf("\n");
    }


    return 0;
}