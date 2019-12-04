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

SET(BUILD_REMOTE_SHELL "ON")

SET(NBI_LIB_PATH "${CMAKE_SOURCE_DIR}/../xranc-nb-api-src/xranc_nbi.a")
SET(HIREDIS_LIB_PATH "/usr/local/lib/libhiredis.a")
SET(NBI_SOURCE_PATH "${CMAKE_SOURCE_DIR}/../xranc-nb-api-src")
SET(HIREDIS_SOURCE_PATH "/usr/local/include/hiredis")
SET(NBI_FLAGS "-I${NBI_SOURCE_PATH} ${NBI_LIB_PATH}")
SET(HIREDIS_FLAGS "-I${HIREDIS_SOURCE_PATH} ${HIREDIS_LIB_PATH}")
SET(COMMON_FLAGS_FOR_GW "-I${CMAKE_SOURCE_DIR}../common/include")

SET(CMAKE_C_FLAGS "-D_GNU_SOURCE -std=gnu99 -Wall -Wextra -Werror -fPIC ${CMAKE_C_FLAGS}")
SET(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG")
SET(CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-unused-parameter -g -std=c++11 -L/usr/local/lib ${COMMON_FLAGS_FOR_GWs} ${NBI_FLAGS} ${HIREDIS_FLAGS} ${CMAKE_CXX_FLAGS}")
SET(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")
SET(CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH} "/usr/local/share/celix/cmake/modules")

find_library(PROTOBUF libprotobuf.a protobuf)
find_library(GRPC libgrpc.a grpc)
find_library(GRPC++ libgrpc++.a grpc++)
find_library(GRPC_UNSECURE libgrpc_unsecure.a grpc_unsecure)
find_package(Protobuf REQUIRED)
find_package(CELIX REQUIRED)

set(CELIX_INCLUDE_DIRS ${CELIX_INCLUDE_DIRS} "/usr/local/include/celix/shell")
message(STATUS ${CELIX_INCLUDE_DIRS})
foreach(item IN ITEMS ${CELIX_INCLUDE_DIRS})
        include_directories(${item})
endforeach()
add_subdirectory(GWCore)
add_subdirectory(Bundles/SBBundle)
add_celix_container(ric-api-gw
    CXX
    BUNDLES
            ${CELIX_BUNDLES_DIR}/shell.zip
            ${CELIX_BUNDLES_DIR}/shell_tui.zip
            ${CELIX_BUNDLES_DIR}/dm_shell.zip
            ${CELIX_BUNDLES_DIR}/remote_shell.zip # for telnet
            GWCore
            SBBundle
)