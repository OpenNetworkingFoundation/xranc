# xranc

## Install libevent2
```
sudo apt-get install libevent2-dev
```

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

### Misc

Command to test sctp connection
```
socat -x -d -d -d - sctp:<ip>:<port>
```
