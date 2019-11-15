SHELL := /bin/bash
ROOT_DIR := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
OS_VENDOR := $(shell lsb_release -i -s)
OS_RELEASE := $(shell lsb_release -r -s)
GRPC_BRANCH := master
NUM_CORES := 4
GRPC_DIR := /tmp/grpc
PROTOBUF_DIR := $(GRPC_DIR)/third_party/protobuf
XRANC_DIR := $(ROOT_DIR)/xranc
XRANC_SBI_DIR := $(ROOT_DIR)/xranc-sb-api-src
XRANC_NBI_DIR := $(ROOT_DIR)/xranc-nb-api-src
XRANC_ENBSIM_DIR := $(ROOT_DIR)/enbsim
XRANC_DB_DIR := $(ROOT_DIR)/database

all: install_prerequisites get_submodules build_xranc-sb build_xranc-nb build_xranc build_enbsim

install_prerequisites:
	@if [[ $(OS_VENDOR) =~ (Ubuntu) ]]; then \
		if [[ $(OS_RELEASE) =~ (16.04) ]]; then \
			echo "WARN: Not fully tested on $(OS_VENDOR) $(OS_RELEASE)."; \
			sudo apt update; \
			sudo apt-get install -y libevent2-dev libjsoncpp-dev libsctp-dev; \
		elif [[ $(OS_RELEASE) =~ (18.04) ]]; then \
			sudo apt update; \
			sudo apt-get install libevent-dev libjsoncpp-dev libsctp-dev; \
		fi \
	else \
		echo "Unsupported OS - Ubuntu 18.04 is recommended"; \
		exit 1; \
	fi
	sudo apt-get install -y build-essential autoconf git pkg-config automake libtool curl make g++ unzip;
	git clone -b $(GRPC_BRANCH) https://github.com/grpc/grpc $(GRPC_DIR); \
	cd $(GRPC_DIR) && git submodule update --init && echo "--- installing protobuf ---" && cd $(PROTOBUF_DIR) && \
	./autogen.sh && ./configure --enable-shared && make -j$(NUM_CORES) && sudo make install && make clean && sudo ldconfig && \
	echo "--- installing grpc ---" && cd $(GRPC_DIR) && make -j$(NUM_CORES) && sudo make install && make clean && sudo ldconfig;

get_submodules:
	cd $(ROOT_DIR) && git submodule init && git submodule update;
	
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
