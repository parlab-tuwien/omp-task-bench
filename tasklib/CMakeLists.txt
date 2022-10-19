cmake_minimum_required(VERSION 3.0)
project(tasklib C)

set(CMAKE_C_STANDARD 99)

add_library(tasklib SHARED src/tasklib.c)
set_target_properties(tasklib PROPERTIES PUBLIC_HEADER "include/tasklib.h")

include(GNUInstallDirs)
install(TARGETS tasklib
        PUBLIC_HEADER
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
