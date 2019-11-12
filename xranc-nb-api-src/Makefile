CXX = g++
AR = ar
RCS = rcs
CXFLAGS = -Wall -Wextra -g -std=c++11 -I.
LDFLAGS = -L/usr/local/lib `pkg-config --libs protobuf grpc++` -pthread -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed -ldl
NBI_LIB ?= xranc_nbi.a

PROTOC = protoc
GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH = `which $(GRPC_CPP_PLUGIN)`
PROTOC_PATH = ./protobufs
PROTOC_SRCS = $(wildcard ./protobufs/*.proto)
PROTOC_CPP_SRCS = $(PROTOC_SRCS:.proto=.pb.cc)
PROTOC_GRPC_SRCS = $(PROTOC_SRCS:.proto=.grpc.pb.cc)
GRPC_HANDLER_CLIENTS_SRCS = $(wildcard ./gRPCHandlers/gRPCClients/*.cpp)
GRPC_HANDLER_SERVERS_SRCS = $(wildcard ./gRPCHandlers/gRPCServers/*.cpp)
GRPC_HANDLER_PARAMS_SRCS = $(wildcard ./gRPCHandlers/gRPCParams/*.cpp)

all: $(NBI_LIB)

%.o: %.cpp %.cc $(PROTOC_CPP_SRCS) $(PROTOC_GRPC_SRCS) $(GRPC_HANDLER_CLIENTS_SRCS) $(GRPC_HANDLER_SERVERS_SRCS) $(GRPC_HANDLER_PARAMS_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

%.grpc.pb.cc: %.proto
	$(PROTOC) -I $(PROTOC_PATH) --grpc_out=./protobufs --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $<

%.pb.cc: %.proto
	$(PROTOC) -I $(PROTOC_PATH) --cpp_out=./protobufs $<

comp: $(PROTOC_CPP_SRCS) $(PROTOC_GRPC_SRCS) $(GRPC_HANDLER_CLIENTS_SRCS) $(GRPC_HANDLER_SERVERS_SRCS) $(GRPC_HANDLER_PARAMS_SRCS)

$(NBI_LIB): $(PROTOC_CPP_SRCS:.cc=.o) $(PROTOC_GRPC_SRCS:.cc=.o) $(GRPC_HANDLER_CLIENTS_SRCS:.cpp=.o) $(GRPC_HANDLER_SERVERS_SRCS:.cpp=.o) $(GRPC_HANDLER_PARAMS_SRCS:.cpp=.o)
	$(AR) $(RCS) $@ $(PROTOC_CPP_SRCS:.cc=.o) $(PROTOC_GRPC_SRCS:.cc=.o) $(GRPC_HANDLER_CLIENTS_SRCS:.cpp=.o) $(GRPC_HANDLER_SERVERS_SRCS:.cpp=.o) $(GRPC_HANDLER_PARAMS_SRCS:.cpp=.o)

clean:
	rm -f $(NBI_LIB)
	rm -f $(PROTOC_PATH)/*.cc $(PROTOC_PATH)/*.h $(PROTOC_PATH)/*.o
	rm -f $(GRPC_HANDLER_CLIENTS_SRCS:.cpp=.o)
	rm -f $(GRPC_HANDLER_SERVERS_SRCS:.cpp=.o)
	rm -f $(GRPC_HANDLER_PARAMS_SRCS:.cpp=.o)

