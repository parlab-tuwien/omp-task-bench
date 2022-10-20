/*
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
 *  hetero_util.h
 * 
 *  @brief Functions to generate heterogeneous workloads using exponential distribution
 *  @author Lukas Briem
 *  @date February 2022
 **/


#ifndef SRC_HETERO_UTIL_H
#define SRC_HETERO_UTIL_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <time.h>

/**
 * @brief computes an exponential distribution (workload) of n elements and returns it as an pointer
 *
 * @param lambda parameter of the exponential distribution
 * @param n number of elements which should be generated
 * @return int* pointer to the workload
 */
int *expo_dist(double lambda, long int n);


/**
 * @brief draws randomly from an exponential distribution (has to be seeded before usage)
 * 
 * @param lambda parameter of the exponential distribution
 * @return int randomly drawn value (minimum 1)
 */
int draw_random_expo(double lambda);

#endif /* SRC_HETERO_UTIL */
