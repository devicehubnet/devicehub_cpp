#ifndef DEVICEHUB_H
#define DEVICEHUB_H

#include "mosquittopp.h"
#include <uuid/uuid.h>
#include <stdint.h>
#include <iostream>
#include <map>

using namespace std;

namespace devicehub {

    typedef uuid_t device_uuid_t;
    typedef uuid_t api_key_t;
    typedef uint64_t project_id_t;

    class DeviceHub : public mosqpp::mosquittopp {
    public:
        DeviceHub(project_id_t project_id, device_uuid_t device_id, api_key_t api_key);
        ~DeviceHub();
        void connect();
        void disconnect();
        void send();
        void addValue(std::string name, double value);

    private:
        std::map<std::string, double> sensorMap;
    };
}

#endif // DEVICEHUB_H
