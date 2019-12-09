# xranc

## Quick start
```
git clone https://github.com/OpenNetworkingFoundation/xranc.git
cd xranc
make
```

**NOTE**: Makefile in the root directory has four options:
- make or make all: install everything in this repo
- make utilities: only install utilities and dependencies
- make build: build xranc interfaces, xranc, and enbsim
- make clean: clean all object and binary files

## Manual steps to install xRANc
### Install dependencies
```
sudo apt-get install libevent2-dev # for Ubuntu 16.04
sudo apt-get install libevent-dev # for Ubuntu 18.04
sudo apt-get install libjsoncpp-dev
sudo apt install libsctp-dev
```

#### Install gRPC
Please follow this [link](https://github.com/grpc/grpc/blob/v1.25.0/BUILDING.md)

#### Install hiredis
```
git clone https://github.com/redis/hiredis
cd /path/to/hiredis
make
sudo make install
```

#### Clone with SSH or HTTPS
```
git clone git@github.com:OpenNetworkingFoundation/xranc.git
git clone https://github.com/OpenNetworkingFoundation/xranc.git
```

#### Update submodules
```
git submodule init
git submodule update
```

#### Build and run
```
cd xranc
make
./xranc
```
This would start the xran-controller listening for enodeb to connect. Currently using the Java enodeb simulator that was developed for the xran-controller ONOS app. Check out this [link(https://wiki.onosproject.org/display/ONOS/xRAN+Controller+Integration)] for how to build and run the enodeb simulator.

### enbsim
enbsim runs on the same machine as xranc.
```
cd enbsim; make clean; make
```
enbsim uses private ip addresses 127.0.0.0/8 on loopback. Run the config-ip.sh script to configure.
```
sudo enbsim/config-ip.sh
```
Start enbsim with 20 enodebs. Currently it only responds to cell config requests. If xranc is listening on 127.0.0.1 port 5555, the following command will start 20 enodebs:
```
./enbsim 127.0.0.1 5555 20 1

### Deploy 


```
#### Misc

Command to test sctp connection
```
socat -x -d -d -d - sctp:<ip>:<port>
```
