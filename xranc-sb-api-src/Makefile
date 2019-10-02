include Makefile.am.libasncodec

CFLAGS += $(ASN_MODULE_CFLAGS) -DPDU=XRANCPDU -I.
ASN_LIBRARY ?= libasncodec.a

all: $(ASN_LIBRARY)

$(ASN_LIBRARY): $(ASN_MODULE_SRCS:.c=.o)
	$(AR) rcs $@ $(ASN_MODULE_SRCS:.c=.o)

.SUFFIXES:
.SUFFIXES: .c .o

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(ASN_PROGRAM) $(ASN_LIBRARY)
	rm -f $(ASN_MODULE_SRCS:.c=.o)

regen: regenerate-from-asn1-source

regenerate-from-asn1-source:
	asn1c -fcompound-names -pdu=XRANCPDU ../xranc-sb-api/xRAN-API-IEs.asn1 ../xranc-sb-api/xRAN-API-PDUs.asn1
