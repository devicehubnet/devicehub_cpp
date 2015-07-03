DeviceHub.net C++ library
=========================

This library wraps around DeviceHub.net's REST and MQTT APIs and allows you to easily connect to the DeviceHub.net PaaS from C++ code.

Requirements
------------
* C++11 compiler (gcc or clang)
* cmake build system
* mosquitto C & C++ library
* libcurl
* openssl development package
* uuid-dev

Installation
------------

Linux
-----
Install dependencies:

For Ubuntu:
```
sudo add-apt-repository ppa:mosquitto-dev/mosquitto-ppa
sudo apt-get update
sudo apt-get install cmake libmosquitto-dev libmosquittopp-dev libcurl4-openssl-dev uuid-dev libssl-dev
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

A version of this library specialy crafted for the Arduino, using PubSubClient will be released soon.
