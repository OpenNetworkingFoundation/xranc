# Copyright 2019-present Open Networking Foundation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.4)
project(ric-api-gw CXX)

SET(CMAKE_C_FLAGS "-D_GNU_SOURCE -std=gnu99 -Wall -Wextra -Werror -fPIC ${CMAKE_C_FLAGS}")
SET(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG")
SET(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
SET(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH} "/usr/local/share/celix/cmake/modules")

find_package(CELIX REQUIRED)

set(CELIX_INCLUDE_DIRS ${CELIX_INCLUDE_DIRS} "/usr/local/include/celix/shell")
message(STATUS ${CELIX_INCLUDE_DIRS})
foreach(item IN ITEMS ${CELIX_INCLUDE_DIRS})
        include_directories(${item})
endforeach()
add_subdirectory(GWCore)
add_celix_container(ric-api-gw
    CXX
    BUNDLES
            ${CELIX_BUNDLES_DIR}/shell.zip
            ${CELIX_BUNDLES_DIR}/shell_tui.zip
            ${CELIX_BUNDLES_DIR}/dm_shell.zip
            GWCore
)