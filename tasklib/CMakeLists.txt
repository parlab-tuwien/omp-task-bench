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
