/*
  Copyright (C) 2020-2022 OMPTB Contributors

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
 * util.h
 *
 * @brief header for utility benchmark harness functions
 * @author Sascha Hunold 
 * @author Lukas Briem
 * @date June 2020 - Februray 2022
 * @copyright GNU GPLv3
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
