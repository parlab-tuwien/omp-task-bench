
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
