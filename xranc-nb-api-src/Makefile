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
PB_CPP_SRCS = $(wildcard $(PB_DIR_PATH)/*.pb.cc)
PB_GRPC_SRCS = $(wildcard $(PB_DIR_PATH)/*.grpc.pb.cc)
GRPC_API_PATH = ./gRPCAPIs
GRPC_API_CPP_PATH = $(GRPC_API_PATH)/cpp
GRPC_API_SERVERS_SRCS = $(wildcard $(GRPC_API_CPP_PATH)/gRPCServers/*.cpp)
GRPC_API_CLIENTS_SRCS = $(wildcard $(GRPC_API_CPP_PATH)/gRPCClients/*.cpp)
GRPC_API_PARAMS_SRCS = $(wildcard $(GRPC_API_CPP_PATH)/gRPCParams/*.cpp)

all: $(NBI_LIB)

%.grpc.pb.cc: %.proto
	mkdir -p $(PB_DIR_PATH)
	$(PROTOC) -I $(PROTOS_PATH) --grpc_out=$(PB_DIR_PATH) --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $<

%.pb.cc: %.proto
	mkdir -p $(PB_DIR_PATH)
	$(PROTOC) -I $(PROTOS_PATH) --cpp_out=$(PB_DIR_PATH) $<

%.o: %.cpp %.cc 
	$(CXX) $(CXFLAGS) -o $@ -c $<

$(NBI_LIB):| $(PROTOS_SRC:.proto=.pb.cc) $(PROTOS_SRC:.proto=.grpc.pb.cc) $(PB_CPP_SRCS:.cc=.o) $(PB_GRPC_SRCS:.cc=.o) $(GRPC_API_PARAMS_SRCS:.cpp=.o) $(GRPC_API_SERVERS_SRCS:.cpp=.o) $(GRPC_API_CLIENTS_SRCS:.cpp=.o)
	$(AR) $(RCS) $@ $(PB_CPP_SRCS:.cc=.o) $(PB_GRPC_SRCS:.cc=.o) $(GRPC_API_PARAMS_SRCS:.cc=.o) $(GRPC_API_SERVERS_SRCS:.cc=.o) $(GRPC_API_CLIENTS_SRCS:.cc=.o)

clean:
	rm -f $(NBI_LIB)
	rm -rf $(PB_DIR_PATH)
	rm -f $(GRPC_API_PATH)/cpp/gRPCServers/*.o
	rm -f $(GRPC_API_PATH)/cpp/gRPCClients/*.o
	rm -f $(GRPC_API_PATH)/cpp/gRPCParams/*.o