/*
  Copyright (C) 2022 Lukas Briem

  This file is part of OMPTB.
 
  OMPTB is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  OMPTB is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OMPTB.  If not, see <https://www.gnu.org/licenses/gpl-3.0.html>.
*/

/**
 *  hetero_util.c
 *
 *  @brief Implementation of @see hetero_util.h
 *  @author Lukas Briem
 *  @date February 2022
 **/

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
