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
 * tasklib.c
 *
 * @brief work functions
 * @author Sascha Hunold 
 * @date June 2020 - June 2022
 * @copyright GNU GPLv3
 */

#include <stdio.h>
#include <stdlib.h>

long long fib(long long n) {
    if (n <= 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}

void task1(double *a, double *b, int n) {
    int i;
    for (i = 0; i < n; i++) {
        a[i] = a[i] + b[i];
    }
}

double add_bench(long long n) {
    double res = 0.0;
    for (long long i = 0; i < n; i++) {
        //res += -1+2*(double)rand()/(double)RAND_MAX;
        res += (double) i;
    }
    return res;
}
