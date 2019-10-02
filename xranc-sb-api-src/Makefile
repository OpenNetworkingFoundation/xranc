all:
	make -f converter-example.mk

regen:
	asn1c -fcompound-names -pdu=XRANCPDU ../xranc-sb-api/*.asn1

clean:
	make -f converter-example.mk clean
