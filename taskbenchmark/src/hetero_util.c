/**
 * hetero_util.c
 *
 * @brief Implementation of @see hetero_util.h
 * @author Lukas Briem
 * @date February 2022
 */

#include "hetero_util.h"

#define MAX(a, b) (((a) > (b)) ? (a) : (b))


int *expo_dist(double lambda, long int n) {
    int *expo_distribution = (int *) malloc(sizeof(int) * n);
    for (size_t i = 0; i < n; i++) {
        expo_distribution[i] = draw_random_expo(lambda);
    }
    return expo_distribution;
}

int draw_random_expo(double lambda) {
    // scale to range [0,1]
    double u = rand() / (RAND_MAX + 1.0);
    return MAX((int) (-log(1 - u) / lambda), 1);
}
