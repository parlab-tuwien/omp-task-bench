# This file is part of OMPTB.
#
# OMPTB is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.

# OMPTB is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with OMPTB.  If not, see <https://www.gnu.org/licenses/gpl-3.0.html>.

cmake_minimum_required(VERSION 3.10)

project(taskbenchmark C)

set(CMAKE_C_STANDARD 99)

find_package(OpenMP REQUIRED)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")


set(TASKLIB_PATH "${CMAKE_SOURCE_DIR}/../tasklib")
message(STATUS "Searching tasklib...")
find_library(TASKLIB
        NAMES tasklib
        PATHS ${TASKLIB_PATH})
INCLUDE_DIRECTORIES("${TASKLIB_PATH}/include")

message(STATUS "tasklib: ${TASKLIB}")


set(TASKBENCHMARK_SRC_FILES
${SRC_DIR}/omp_bench.c
${SRC_DIR}/hetero_util.c
${SRC_DIR}/util.c
)

add_executable(omp_bench
${TASKBENCHMARK_SRC_FILES}
)

target_link_libraries(omp_bench PUBLIC OpenMP::OpenMP_C ${TASKLIB} m)
