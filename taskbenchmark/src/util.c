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
 *  @copyright GNU GPLv3
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "util.h"

void write_trace_file(const char *outfname, struct omp_trace_data *data) {
    int i;
    FILE *fh;

    fh = fopen(outfname, "w");

    fprintf(fh,
            "<?xml version=\"1.0\"?>\n \
<grid_schedule>\n\
<meta_info>\n\
</meta_info>\n\
<grid_info>\n\
<info name=\"nb_clusters\" value=\"1\"/>\n\
<clusters>\n\
<cluster id=\"0\" hosts=\"%d\" first_host=\"0\"/>\n\
</clusters>\n\
</grid_info>\n\
<node_infos>\n",
            data->p);

    for (i = 0; i < data->n; i++) {
        fprintf(fh,
                "<node_statistics>\n\
<node_property name=\"id\" value=\"%d\"/>\n\
<node_property name=\"type\" value=\"computation\"/>\n\
<node_property name=\"start_time\" value=\"%f\"/>\n\
<node_property name=\"end_time\" value=\"%f\"/>\n\
<configuration>\n\
<conf_property name=\"cluster_id\" value=\"0\"/>\n\
<conf_property name=\"host_nb\" value=\"1\"/>\n\
<host_lists>\n\
  <hosts start=\"%d\" nb=\"1\"/>\n\
</host_lists>\n\
</configuration>\n\
</node_statistics>\n",
                i, (data->stimes[i] - data->stimes[0]) * 1e6, (data->etimes[i] - data->stimes[0]) * 1e6, data->tids[i]);

    }

    fprintf(fh, "</node_infos>\n\
</grid_schedule>\n");

    fclose(fh);
}


void write_events_csv(const char *outfname, struct omp_trace_data *data, bool hetero) {
    int i;
    FILE *fh;

    fh = fopen(outfname, "w");

    fprintf(fh, "#@p=%d\n", data->p);
    fprintf(fh, "#@n=%d\n", data->n);

    if (hetero) {
        fprintf(fh, "#@lambda=%f\n", data->lambda);
    } else {
        fprintf(fh, "#@m=%d\n", data->m);
    }

    fprintf(fh, "#@s=%d\n", data->s);
    fprintf(fh, "#@global_start=%f\n", data->global_start);
    fprintf(fh, "#@global_end=%f\n", data->global_end);
    fprintf(fh, "#@running_time_s=%f\n", data->global_end - data->global_start);
    fprintf(fh, "#@mean_task_time_millis=%f\n", data->mean_task_time);

    fprintf(fh, "taskid;tid;start;end\n");

    for (i = 0; i < data->n; i++) {
        fprintf(fh, "%10d;%2d;%f;%f\n",
                i, data->tids[i], data->stimes[i], data->etimes[i]);

    }

    fclose(fh);
}

void write_thread_csv(const char *outfname, struct omp_stats_data *data, bool hetero) {

    int i;
    FILE *fh;
    int is_stdout = 0;
    double *task_time_per_tid;
    int *count_tid;

    if (strcmp(outfname, "/dev/stdout") == 0) {
        is_stdout = 1;
    }

    if (is_stdout == 1) {
        fh = stdout;
    } else {
        fh = fopen(outfname, "w");
    }

    fprintf(fh, "#@p=%d\n", data->trace_data->p);
    fprintf(fh, "#@n=%d\n", data->trace_data->n);

    if (hetero) {
        fprintf(fh, "#@lambda=%f\n", data->trace_data->lambda);
    } else {
        fprintf(fh, "#@m=%d\n", data->trace_data->m);
    }

    fprintf(fh, "#@s=%d\n", data->trace_data->s);
    fprintf(fh, "#@global_start=%.6f\n", data->trace_data->global_start);
    fprintf(fh, "#@global_end=%.6f\n", data->trace_data->global_end);
    fprintf(fh, "#@running_time_s=%.6f\n", data->trace_data->global_end - data->trace_data->global_start);
    fprintf(fh, "#@mean_task_time_millis=%f\n", data->trace_data->mean_task_time);
    fprintf(fh, "tid;start_ms;spawned_ms;task_count;task_time_per_tid_ms;task_wait_ms\n");

    count_tid = calloc(data->trace_data->p, sizeof(int));
    task_time_per_tid = calloc(data->trace_data->p, sizeof(double));
    for (i = 0; i < data->trace_data->n; i++) {
        count_tid[data->trace_data->tids[i]]++;
        task_time_per_tid[data->trace_data->tids[i]] += data->trace_data->etimes[i] - data->trace_data->stimes[i];
    }


    for (i = 0; i < data->trace_data->p; i++) {
        double tasktime_per_tid = 0.0;
        fprintf(fh, "%3d;%12.3f;%12.3f;%10d;%.6f;%.6f\n", i,
                (data->tstart[i] - data->trace_data->global_start) * 1e3,
                (data->tspawned[i] - data->trace_data->global_start) * 1e3,
                count_tid[i],
                task_time_per_tid[i] * 1e3,
                (data->trace_data->global_end - data->tstart[i] - task_time_per_tid[i]) * 1e3
        );
    }

    free(task_time_per_tid);
    free(count_tid);

    if (is_stdout == 0) {
        fclose(fh);
    }

}

void write_profile_csv(const char *outfname, int* task_count, int p, int n, int m, double lambda, bool hetero) {

    int i;
    FILE *fh;
    int is_stdout = 0;

    if (strcmp(outfname, "/dev/stdout") == 0) {
        is_stdout = 1;
    }

    if (is_stdout) {
        fh = stdout;
    } else {
        fh = fopen(outfname, "w");
    }

    fprintf(fh, "#@p=%d\n", p);
    fprintf(fh, "#@n=%d\n", n);

    if (hetero) {
        fprintf(fh, "#@lambda=%f\n", lambda);
    } else {
        fprintf(fh, "#@m=%d\n", m);
    }

    fprintf(fh, "tid;num_tasks\n");

    long long sum = 0;
    for (i=0; i<p; i++) {
        fprintf(fh, "%d;%d\n", i, task_count[i*FS_OFFSET]);
        sum += task_count[i*FS_OFFSET];
    }

    if (!is_stdout) {
        fclose(fh);
    }

}
