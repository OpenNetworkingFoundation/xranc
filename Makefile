SHELL := /bin/bash
ROOT_DIR := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
OS_VENDOR := $(shell lsb_release -i -s)
OS_RELEASE := $(shell lsb_release -r -s)
GRPC_BRANCH := v1.20.0
GRPC_DIR := $(ROOT_DIR)/common/grpc
HIREDIS_TAG := v0.14.0
HIREDIS_DIR := $(ROOT_DIR)/common/hiredis
PROTOBUF_DIR := $(GRPC_DIR)/third_party/protobuf
XRANC_DIR := $(ROOT_DIR)/xranc
XRANC_SBI_DIR := $(ROOT_DIR)/xranc-sb-api-src
XRANC_NBI_DIR := $(ROOT_DIR)/xranc-nb-api-src
XRANC_ENBSIM_DIR := $(ROOT_DIR)/enbsim
XRANC_DB_DIR := $(ROOT_DIR)/database

all: modules utilities build

build: build_xranc-sb build_xranc-nb build_xranc build_enbsim

modules:
	cd $(ROOT_DIR) && git submodule init && git submodule update;
	cd $(GRPC_DIR) && git fetch --all && git checkout $(GRPC_BRANCH);
	cd $(HIREDIS_DIR) && git fetch --all && git checkout $(HIREDIS_TAG);

utilities:
	@if [[ $(OS_VENDOR) =~ (Ubuntu) ]]; then \
		if [[ $(OS_RELEASE) =~ (16.04) ]]; then \
			echo "WARN: Not fully tested on $(OS_VENDOR) $(OS_RELEASE)."; \
			sudo apt update; \
			sudo apt install -y libevent2-dev libjsoncpp-dev libsctp-dev; \
		elif [[ $(OS_RELEASE) =~ (18.04) ]]; then \
			sudo apt update; \
            sudo apt install libevent-dev libjsoncpp-dev libsctp-dev; \
		fi \
	else
		echo "Unsupported OS - Ubuntu 18.04 is recommended"; \
		exit 1;
	fi
	sudo apt install -y build-essential autoconf git pkg-config automake libtool curl make g++ unzip;
	# build gRPC
	cd $(GRPC_DIR) && make && sudo make install;
	# build protobuf
	cd $(PROTOBUF_DIR) && make && sudo make install;
	# build hiredis
	cd $(HIREDIS_DIR) && make && sudo make install;

build_xranc-sb:
	cd $(XRANC_SBI_DIR) && make;

build_xranc-nb:
	cd $(XRANC_NBI_DIR) && make;

build_xranc:| build_xranc-sb build_xranc-nb
	cd $(XRANC_DIR) && make;

build_enbsim:| build_xranc-sb
	cd $(XRANC_ENBSIM_DIR) && make;

clean_sbi:
	cd $(XRANC_SBI_DIR) && make clean;

clean_nbi:
	cd $(XRANC_SBI_DIR) && make clean;

clean_xranc:
	cd $(XRANC_DIR) && make clean;

clean_enbsim:
	cd $(XRANC_ENBSIM_DIR) && make clean;

clean:| clean_sbi clean_nbi clean_xranc clean_enbsim
	@echo "All cleaned"
