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

SET(NBI_LIB_PATH "${CMAKE_SOURCE_DIR}/../xranc-nb-api-src/xranc_nbi.a")
SET(HIREDIS_LIB_PATH "/usr/local/lib/libhiredis.a")

add_celix_bundle(RedisBundle
        VERSION 1.0.0
        SOURCES
        ./Activator/RedisBundleActivator.cpp
        ./Component/RedisBundleComponent.cpp
)

include_directories(
        ../APIs
        ./Activator
        ./Component
)

target_link_libraries(RedisBundle -Wl,--no-undefined -Wl,--whole-archive ${CELIX_DM_STATIC_CXX_LIB} -Wl,--no-whole-archive ${CELIX_LIBRARIES} -lhiredis ${NBI_LIB_PATH} ${HIREDIS_LIB_PATH})

message(STATUS ${HIREDIS_LIB_PATH} ${NBI_LIB_PATH})
message(STATUS ${CMAKE_CXX_FLAGS})
