# xranc

## Install dependencies
```
sudo apt-get install libevent2-dev # for Ubuntu 16.04
sudo apt-get install libevent-dev # for Ubuntu 18.04
sudo apt-get install libjsoncpp-dev
sudo apt install libsctp-dev
```

### Install gRPC
Please follow this [link](https://github.com/grpc/grpc/blob/v1.25.0/BUILDING.md)

### Clone with SSH or HTTPS
```
git clone git@github.com:OpenNetworkingFoundation/xranc.git
git clone https://github.com/OpenNetworkingFoundation/xranc.git
```

### Update submodules
```
git submodule init
git submodule update
```

### Build and run
```
cd xranc
make
./xranc
```
This would start the xran-controller listening for enodeb to connect. Currently using the Java enodeb simulator that was developed for the xran-controller ONOS app. Check out this [link(https://wiki.onosproject.org/display/ONOS/xRAN+Controller+Integration)] for how to build and run the enodeb simulator.

### Misc

Command to test sctp connection
```
socat -x -d -d -d - sctp:<ip>:<port>
```
