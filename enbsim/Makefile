CXX = g++
LD = g++
CXXFLAGS = -Wall -Wextra -g -std=c++11 -Wno-unused-parameter
CXXFLAGS += -DPDU=XRANCPDU -I. -I../xranc-sb-api-src -I../common/include
LIBS += -lm -levent -lpthread -ljsoncpp
ASN_LIBRARY ?= libasncodec.a
ENBSIM ?= enbsim
ENBSIM_SRCS = \
	main.cpp \
	enbsim.cpp \
	config.cpp \
	context.cpp \
	dispatch.cpp \
	cell_config.cpp \
	ue.cpp

all: $(ENBSIM) $(ENBSIM)

$(ENBSIM): ../xranc-sb-api-src/$(ASN_LIBRARY) $(ENBSIM_SRCS:.cpp=.o)
	$(LD) -o $@ $^ ../xranc-sb-api-src/$(ASN_LIBRARY) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c  $<

clean:
	rm -f $(ENBSIM)
	rm -f $(ENBSIM_SRCS:.cpp=.o)
