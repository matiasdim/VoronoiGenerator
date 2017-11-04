#include <stdio.h>
#include <stdlib.h>
#include "math.h"

#define THREADS_PER_BLOCK 1024

__global__ void cu_voronoi(int *matrix_d, int *seeds_d, int numberOfSeeds, int width, int sizeOfArray) {
 int x = blockIdx.x * blockDim.x + threadIdx.x;
 int i;
 if (x < sizeOfArray && matrix_d[x] != -1) {
     double minDistance = INFINITY;
     double distance;
     int currentSeed;
     int matrixI = x/width;
     int matrixJ = x % width;
     for (i = 0; i < numberOfSeeds; i++) {
        int candidateSeed = seeds_d[i];
        int seedI = candidateSeed/width;
        int seedJ = candidateSeed % width;
        double xDistance = matrixI - seedI;
        double yDistance = matrixJ - seedJ;
        double distanceSum = pow(xDistance, 2)  + pow(yDistance, 2);
        distance = sqrt(distanceSum);
        if (distance < minDistance) {
            minDistance = distance;
            currentSeed = i;
        }
     }
    matrix_d[x] = currentSeed;
 }
}

extern "C" void voronoi(int *matrix, int *seeds, int numberOfSeeds, int width, int height) {
    int *matrix_d;
    int *seeds_d;
    int sizeOfArray = width * height;
    cudaMalloc((void**) &matrix_d, sizeof(int) * sizeOfArray);
    cudaMalloc((void**) &seeds_d, sizeof(int) * numberOfSeeds);


    cudaMemcpy(matrix_d, matrix, sizeof(int) * sizeOfArray, cudaMemcpyHostToDevice);
    cudaMemcpy(seeds_d, seeds, sizeof(int) * numberOfSeeds, cudaMemcpyHostToDevice);
    int blocks = ceil((float)sizeOfArray/THREADS_PER_BLOCK);
    cu_voronoi <<<blocks, THREADS_PER_BLOCK>>> (matrix_d, seeds_d, numberOfSeeds, width, sizeOfArray);

    cudaMemcpy(matrix, matrix_d, sizeof(int) * sizeOfArray, cudaMemcpyDeviceToHost);

    cudaFree(matrix_d);
    cudaFree(seeds_d);
}
