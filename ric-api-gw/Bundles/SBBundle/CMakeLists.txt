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

find_library(PROTOBUF libprotobuf.a protobuf)
find_library(GRPC libgrpc.a grpc)
find_library(GRPC++ libgrpc++.a grpc++)
SET(NBI_LIB_PATH "${CMAKE_SOURCE_DIR}/../xranc-nb-api-src/xranc_nbi.a")

add_custom_command(
        OUTPUT
                ${CMAKE_CURRENT_SOURCE_DIR}/API/e2-interface/e2-interface.grpc.pb.cc
        COMMAND
                protoc -I ${CMAKE_CURRENT_SOURCE_DIR}/API/e2-interface --grpc_out=${CMAKE_CURRENT_SOURCE_DIR}/API/e2-interface --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ${CMAKE_CURRENT_SOURCE_DIR}/API/e2-interface/e2-interface.proto
)

add_custom_command(
        OUTPUT
                ${CMAKE_CURRENT_SOURCE_DIR}/API/e2-interface/e2-interface.pb.cc
        COMMAND
                protoc -I ${CMAKE_CURRENT_SOURCE_DIR}/API/e2-interface --cpp_out=${CMAKE_CURRENT_SOURCE_DIR}/API/e2-interface ${CMAKE_CURRENT_SOURCE_DIR}/API/e2-interface/e2-interface.proto
)

add_celix_bundle(SBBundle
        VERSION 1.0.0
        SOURCES
        ./Activator/SBBundleActivator.cpp
        ./Component/SBBundleComponent.cpp
        ./gRPCHandler/gRPCServerImpls/gRPCServerImpl-CellConfigReport.cpp
        ./gRPCHandler/gRPCServerImpls/gRPCServerImpl-UEAdmissionStatus.cpp
        ./gRPCHandler/gRPCServerImpls/gRPCServerImpl-UEContextUpdate.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/API/e2-interface/e2-interface.grpc.pb.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/API/e2-interface/e2-interface.pb.cc
)

include_directories(
        ../../APIs
        ./Activator
        ./Component
        ./gRPCHandler/gRPCServerImpls
        ./API/e2-interface
)

target_link_libraries(SBBundle -Wl,--no-undefined -Wl,--whole-archive ${CELIX_DM_STATIC_CXX_LIB} -Wl,--no-whole-archive ${CELIX_LIBRARIES} -lprotobuf -pthread -lgrpc++ -lgpr -lgrpc ${NBI_LIB_PATH})

message (STATUS ${PROTOBUF} ${GRPC++} ${GRPC} ${GRPC_UNSECURE} ${NBI_LIB_PATH})
message(STATUS ${CMAKE_CXX_FLAGS})
