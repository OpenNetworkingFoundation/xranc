CXX = g++
LD = g++
CXXFLAGS = -Wall -Wextra -g -std=c++11
CXXFLAGS += -DPDU=XRANCPDU -I. -I../xranc-sb-api-src -I../xranc-nb-api-src
LIBS += -lm -levent -lpthread -ljsoncpp
LDFLAGS = -L/usr/local/lib `pkg-config --libs protobuf grpc++` -pthread -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed -ldl -lgrpc
ASN_LIBRARY ?= libasncodec.a
NBI_LIBRARY ?= xranc_nbi.a

XRANC_PROGRAM ?= xranc
XRANC_PROGRAM_SRCS = \
	main.cpp \
	config.cpp \
	server.cpp \
	client.cpp \
	workqueue.cpp \
	dispatch.cpp \
	cell_config.cpp \
	handler.cpp
GRPC_HANDLER_CLIENT_IMPL_SRCS = $(wildcard ./gRPCHandlers/gRPCClientImpls/*.cpp)

all: $(XRANC_PROGRAM)

$(XRANC_PROGRAM): ../xranc-sb-api-src/$(ASN_LIBRARY) ../xranc-nb-api-src/$(NBI_LIBRARY) $(GRPC_HANDLER_CLIENT_IMPL_SRCS:.cpp=.o) $(XRANC_PROGRAM_SRCS:.cpp=.o)
	$(LD) -o $@ $^ ../xranc-sb-api-src/$(ASN_LIBRARY) ../xranc-nb-api-src/$(NBI_LIBRARY) $(LIBS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ -c  $<

clean:
	rm -f $(XRANC_PROGRAM)
	rm -f $(XRANC_PROGRAM_SRCS:.cpp=.o)
