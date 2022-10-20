# OMPTB Benchmark Suite

Although OpenMP is heavily used to parallelize for-loops, it also supports
task-parallel programming, which is important for parallelizing irregular
applications. In this work, we focus on the performance of OpenMP runtime
systems for task-based applications. In particular, we investigate the
performance of different OpenMP runtime systems when scheduling a large set
independent tasks of different granularity. To that end, we propose the OpenMP
benchmark *OMPTB*, which features profiling and tracing options that help developers to
reason about the observed performance differences.  

This repository contains the code of our proposed benchmark suite *OMPTB*.  As
mentioned above, the goal of this benchmark suite is to compare the task
implementation of different OpenMP runtime systems using a workload that is the
same in all experiments, making differences in execution time only dependent on
a compiler's runtime system implementation. Thus, the repository is structured
into two parts:
- `tasklib`: Workload library, contains the function `add_bench(n)`, used to create an artificial workload, intended to be built with the same compiler for all benchmarked runtime systems.
- `taskbenchmark`: Benchmark harness, provides the infrastructure for running benchmarks and recording results.

The *OMPTB* benchmark suite has been confirmed to function as intended for the following compilers:
- `tasklib`: `gcc` (11.2.0, 12.1.0)
- `taskbenchmark`: `gcc` (11.2.0, 12.1.0), `clang` (14.0.4), `aocc` (3.2.0), `pgcc` (22.5), `icc` (2021.7.0)

This work is licensed under the [GNU General Public License Version 3](https://www.gnu.org/licenses/gpl-3.0.html).

## Publications

- **A Quantitative Analysis of OpenMP Task Runtime Systems** (link TBD) - Sascha Hunold, Klaus Kraßnitzer / Bench 2022 


## Building and Executing

This section describes how to build the *OMPTB* benchmark suite to facilitate
benchmarking different OpenMP runtime systems. We first build the `tasklib`
library using `gcc` and then proceed by building the `taskbenchmark` executable
using different CMake-supported compilers while statically linking the
previously compiled `tasklib` library to ensure a uniform workload for runtime
system comparison.

_Note: In CMake, the used C compiler is set using the argument `-DCMAKE_C_COMPILER=`_

1. Build `tasklib` with `gcc`:

```bash
$ cd tasklib
$ cmake -DCMAKE_C_COMPILER=gcc .
$ make
```

2. Build `taskbenchmark` with compiler `COMPILER`:


```bash
$ cd taskbenchmark
$ cmake -DCMAKE_C_COMPILER=COMPILER .
$ make
```

After building `taskbenchmark`, the executable `omp_bench` is found in `taskbenchmark/bin/omp_bench`

## Acknoledgements

The authors would like to thank Lukas Briem ([@briemelchen](https://github.com/briemelchen)) for their contributions to this work.
