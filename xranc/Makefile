CXX = g++
LD = g++
CXXFLAGS = -Wall -Wextra -std=c++11
CXXFLAGS += -DPDU=XRANCPDU -I. -I../xranc-sb-api-src
LIBS += -lm
ASN_LIBRARY ?= libasncodec.a
XRANC_PROGRAM ?= xranc
XRANC_PROGRAM_SRCS = \
	main.cpp \
	server.cpp \
	cell_config.cpp

all: $(XRANC_PROGRAM)

$(XRANC_PROGRAM): ../xranc-sb-api-src/$(ASN_LIBRARY) $(XRANC_PROGRAM_SRCS:.cpp=.o)
	$(LD) -o $@ $^ ../xranc-sb-api-src/$(ASN_LIBRARY)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c  $<

clean:
	rm -f $(XRANC_PROGRAM)
	rm -f $(XRANC_PROGRAM_SRCS:.cpp=.o)
