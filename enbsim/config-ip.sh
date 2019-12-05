#!/bin/bash

for IP in {2..20}; do
	ip addr add 127.0.0.${IP}/8 dev lo
done

# EOF
