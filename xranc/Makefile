CXX = g++
LD = g++
CXXFLAGS = -Wall -Wextra -g -std=c++11
CXXFLAGS += -DPDU=XRANCPDU -I. -I../xranc-sb-api-src
LIBS += -lm -levent -lpthread -ljsoncpp
ASN_LIBRARY ?= libasncodec.a
XRANC_PROGRAM ?= xranc
XRANC_PROGRAM_SRCS = \
	main.cpp \
	config.cpp \
	server.cpp \
	client.cpp \
	workqueue.cpp \
	dispatch.cpp \
	cell_config.cpp

all: $(XRANC_PROGRAM)

$(XRANC_PROGRAM): ../xranc-sb-api-src/$(ASN_LIBRARY) $(XRANC_PROGRAM_SRCS:.cpp=.o)
	$(LD) -o $@ $^ ../xranc-sb-api-src/$(ASN_LIBRARY) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c  $<

clean:
	rm -f $(XRANC_PROGRAM)
	rm -f $(XRANC_PROGRAM_SRCS:.cpp=.o)
