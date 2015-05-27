DeviceHub.net C++ library
=========================

This library wraps around DeviceHub.net's REST and MQTT APIs and allows you to easily connect to the DeviceHub.net PaaS from C++ code.

Requirements
------------
* C++11 compiler (gcc or clang)
* mosquitto C & C++ library
* libcurl
* openssl development package
* uuid-dev

Installation
------------

Linux
-----
Install dependancies:
For Ubuntu:
```
add-apt-repository ppa:mosquitto-dev/mosquitto-ppa
sudo apt-get update
sudo apt-get install libmosquitto libmosquittopp libcurl4-openssl-dev uuid-dev libssl-dev
```

Build:
```
mkdir build
cd build
cmake ..
make
```


RaspberryPi
-----------

Intel Edison
------------


Arduino
-------

* enable C++ 11 - http://stackoverflow.com/questions/16224746/how-to-use-c11-to-program-the-arduino
* install Arduino Standard C++ library - https://github.com/maniacbug/StandardCplusplus/blob/master/README.md
