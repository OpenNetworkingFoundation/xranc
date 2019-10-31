CXX = g++
LD = g++
CXXFLAGS = -Wall -Wextra -g -std=c++11
CXXFLAGS += -DPDU=XRANCPDU -I. -I../xranc-sb-api-src
LIBS += -lm -levent -lpthread -ljsoncpp
ASN_LIBRARY ?= libasncodec.a
ENBSIM ?= enbsim
ENBSIM_SRCS = \
	enbsim.cpp \
	config.cpp \
	context.cpp \
	dispatch.cpp \
	cell_config.cpp

all: $(ENBSIM) $(ENBSIM)

$(ENBSIM): ../xranc-sb-api-src/$(ASN_LIBRARY) $(ENBSIM_SRCS:.cpp=.o)
	$(LD) -o $@ $^ ../xranc-sb-api-src/$(ASN_LIBRARY) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c  $<

clean:
	rm -f $(ENBSIM)
	rm -f $(ENBSIM_SRCS:.cpp=.o)
