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

CXX = g++
AR = ar
RCS = rcs
CXFLAGS = -Wall -Wextra -g -std=c++11 -I.
LDFLAGS = -L/usr/local/lib `pkg-config --libs protobuf grpc++` -pthread -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed -ldl
NBI_LIB ?= xranc_nbi.a

PROTOC = protoc
GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH = `which $(GRPC_CPP_PLUGIN)`

PROTOS_PATH = ./protobufs
PROTOS_SRC = $(wildcard $(PROTOS_PATH)/*.proto)
PB_DIR_PATH = ./gRPCAPIs/cpp/gRPCPB
PB_CPP_SRCS = $(addprefix $(PB_DIR_PATH)/, $(basename $(notdir $(PROTOS_SRC))).pb.cc)
PB_GRPC_SRCS = $(addprefix $(PB_DIR_PATH)/, $(basename $(notdir $(PROTOS_SRC))).grpc.pb.cc)
GRPC_API_PATH = ./gRPCAPIs
GRPC_API_CPP_PATH = $(GRPC_API_PATH)/cpp
GRPC_API_SERVERS_SRCS = $(wildcard $(GRPC_API_CPP_PATH)/gRPCServers/*.cpp)
GRPC_API_CLIENTS_SRCS = $(wildcard $(GRPC_API_CPP_PATH)/gRPCClients/*.cpp)
GRPC_API_PARAMS_SRCS = $(wildcard $(GRPC_API_CPP_PATH)/gRPCParams/*.cpp)

all: $(PROTOS_SRC:.proto=.pb.cc) $(PROTOS_SRC:.proto=.grpc.pb.cc) $(PB_CPP_SRCS:.cc=.o) $(PB_GRPC_SRCS:.cc=.o) $(NBI_LIB)

gen_dir:
	mkdir -p $(PB_DIR_PATH)

%.grpc.pb.cc: %.proto gen_dir
	$(PROTOC) -I $(PROTOS_PATH) --grpc_out=$(PB_DIR_PATH) --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $<

%.pb.cc: %.proto gen_dir
	$(PROTOC) -I $(PROTOS_PATH) --cpp_out=$(PB_DIR_PATH) $<

%.o: %.cpp %.cc
	$(CXX) $(CXFLAGS) $(LDFLAGS) -o  $@ -c  $<

$(NBI_LIB):| $(GRPC_API_PARAMS_SRCS:.cpp=.o) $(GRPC_API_SERVERS_SRCS:.cpp=.o) $(GRPC_API_CLIENTS_SRCS:.cpp=.o)
	$(AR) $(RCS) $@ $(PB_CPP_SRCS:.cc=.o) $(PB_GRPC_SRCS:.cc=.o) $(GRPC_API_PARAMS_SRCS:.cpp=.o) $(GRPC_API_SERVERS_SRCS:.cpp=.o) $(GRPC_API_CLIENTS_SRCS:.cpp=.o)

clean:
	rm -f $(NBI_LIB)
	rm -rf $(PB_DIR_PATH)
	rm -f $(GRPC_API_PATH)/cpp/gRPCServers/*.o
	rm -f $(GRPC_API_PATH)/cpp/gRPCClients/*.o
	rm -f $(GRPC_API_PATH)/cpp/gRPCParams/*.o