LIBS += -lm
CFLAGS += $(ASN_MODULE_CFLAGS) -DPDU=XRANCPDU -I. -I../xranc-sb-api-src
ASN_LIBRARY ?= libasncodec.a
XRANC_PROGRAM ?= xranc
XRANC_PROGRAM_SRCS ?= \
	main.c

all: $(XRANC_PROGRAM)

$(XRANC_PROGRAM): ../xranc-sb-api-src/$(ASN_LIBRARY) $(XRANC_PROGRAM_SRCS:.c=.o)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(XRANC_PROGRAM) $(XRANC_PROGRAM_SRCS:.c=.o) $(LDFLAGS) ../xranc-sb-api-src/$(ASN_LIBRARY) $(LIBS)

.SUFFIXES:
.SUFFIXES: .c .o

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(XRANC_PROGRAM)
	rm -f $(XRANC_PROGRAM_SRCS:.c=.o)
