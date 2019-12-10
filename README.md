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
```

### Deploy Redis DB
To store information from/to eNB, DB requires. In this project, we will deploy Redis DB. This DB is running on Docker container.
```
cd ./database
./deployRedisDB.sh
```

NOTE: Of course, you can use your own Redis DB.

### Build and run RIC API Gateway
This gateway was initially designed to translate Redis DB API to gRPC and vice versa. Now, it has been expanding to RIC API Gateway. All of components, e.g., ONOS, XOS, RIC southbound, and Redis DB should be connected with this gateway. This gateway allows all components to communicate with each other. However, this gateway is still under development [current version v0.1.0].

This gateway is designed based on Celix which is one of OSGi frameworks for C/C++ applications. Due to the OSGi properties, we can dynamically start, stop, update, install, and uninstall any application in runtime.

```
cd ric-api-gw
mkdir -p build
cd build
cmake ..
cd deploy/ric-api-gw
./ric-api-gw
```

If you want to see all bundles, please type `lb` while running `ric-api-gw`. Also, `log` command is available to see the log file. To see other command, please push `help` on `ric-api-gw`.

One more big thing is that remote access is also available through `telnet` (port is 6666).

NOTE: please make sure that `REDIS_DB_IP` and `REDIS_DB_PORT` in ./ric-api-gw/Bundles/RedisBundle/Component/RedisBundleComponent.h are correct. Those values are now hard coded but will moved somewhere else to be easily changed by users.


#### Misc

Command to test sctp connection
```
socat -x -d -d -d - sctp:<ip>:<port>
```
