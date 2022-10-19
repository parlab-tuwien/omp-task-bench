/*
 * util.h
 *
 *  Created on: Jul 20, 2020
 *      Author: sascha
 * 
 *  Last updated on: February 2022
 *      Author: Lukas Briem
 */

#ifndef SRC_UTIL_H_
#define SRC_UTIL_H_

struct omp_trace_data {
    int p;
    int n;
    int m;
    double lambda; // only used for heterogeneous runs
    int s;
    double global_start;
    double global_end;
    double mean_task_time;
    double *stimes;
    double *etimes;
    int *tids;
};

struct omp_stats_data {
    struct omp_trace_data *trace_data;

    double *tstart;
    double *tspawned;
};


void write_trace_file(const char *outfname, struct omp_trace_data *data);

void write_events_csv(const char *outfname, struct omp_trace_data *data, bool hetero);

void write_thread_csv(const char *outfname, struct omp_stats_data *data, bool hetero);

void write_profile_csv(const char *outfname, int* task_count, int p, int n, int m, double lambda, bool hetero);

// profiling utility
#define CACHE_LINE_SIZE 64
#define FS_OFFSET (CACHE_LINE_SIZE/sizeof(int))

#endif /* SRC_UTIL_H_ */
