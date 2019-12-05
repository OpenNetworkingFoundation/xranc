#!/bin/bash

g++ redis-msg-gw-poc.cpp ../../xranc-nb-api-src/xranc_nbi.a /usr/local/lib/libhiredis.a -I/usr/local/include/hiredis -I../../xranc-nb-api-src/ -I/usr/local/include/hiredis -Wall -Wextra -g -std=c++11 -o server -L/usr/local/lib `pkg-config --libs protobuf grpc++` -pthread -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed -ldl