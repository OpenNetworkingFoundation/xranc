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
LD = g++
CXXFLAGS = -Wall -Wextra -g -std=c++11 -Wno-unused-parameter
CXXFLAGS += -DPDU=XRANCPDU -I. -I../xranc-sb-api-src -I../xranc-nb-api-src -I../common/include
LIBS += -lm -levent -lpthread -ljsoncpp
LDFLAGS = -L/usr/local/lib `pkg-config --libs protobuf grpc++` -pthread -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed -ldl -lgrpc
ASN_LIBRARY ?= libasncodec.a

PROTOC = protoc
GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH = `which $(GRPC_CPP_PLUGIN)`
PROTOS_PATH = ./api/e2-interface
PROTOS_SRC = $(wildcard $(PROTOS_PATH)/*.proto)
PROTO_GRPC_CPP_SRCS = $(addprefix $(PROTOS_PATH)/, $(notdir $(PROTOS_SRC:.proto=.grpc.pb.cc)))
PROTO_CPP_SRCS = $(addprefix $(PROTOS_PATH)/, $(notdir $(PROTOS_SRC:.proto=.pb.cc)))
GRPC_HANDLER_CLIENT_IMPL_SRCS = $(wildcard ./api/e2-interface/*.cpp)

XRANC_PROGRAM ?= xranc
XRANC_PROGRAM_SRCS = \
	main.cpp \
	config.cpp \
	server.cpp \
	client.cpp \
	workqueue.cpp \
	dispatch.cpp \
	cell_config.cpp \
	handler.cpp \
	bearer.cpp \
	ho.cpp

all: $(PROTOS_SRC:.proto=.grpc.pb.cc) $(PROTOS_SRC:.proto=.pb.cc) $(XRANC_PROGRAM)

$(XRANC_PROGRAM): ../xranc-sb-api-src/$(ASN_LIBRARY) $(GRPC_HANDLER_CLIENT_IMPL_SRCS:.cpp=.o) $(PROTO_GRPC_CPP_SRCS:.cc=.o) $(PROTO_CPP_SRCS:.cc=.o) $(XRANC_PROGRAM_SRCS:.cpp=.o)
	$(LD) -o $@ $^ ../xranc-sb-api-src/$(ASN_LIBRARY) $(LIBS) $(LDFLAGS)

%.o: %.cpp %.cc
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ -c  $<

%.grpc.pb.cc: %.proto
	$(PROTOC) -I $(PROTOS_PATH) --grpc_out=$(PROTOS_PATH) --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $<

%.pb.cc: %.proto
	$(PROTOC) -I $(PROTOS_PATH) --cpp_out=$(PROTOS_PATH) $<

clean:
	rm -f $(XRANC_PROGRAM)
	rm -f $(XRANC_PROGRAM_SRCS:.cpp=.o)
	rm -f $(GRPC_HANDLER_CLIENT_IMPL_SRCS:.cpp=.o)
	rm -f $(PROTO_GRPC_CPP_SRCS)
	rm -f $(PROTO_GRPC_CPP_SRCS:.cc=.h)
	rm -f $(PROTO_GRPC_CPP_SRCS:.cc=.o)
	rm -f $(PROTO_CPP_SRCS)
	rm -f $(PROTO_CPP_SRCS:.cc=.h)
	rm -f $(PROTO_CPP_SRCS:.cc=.o)
	
