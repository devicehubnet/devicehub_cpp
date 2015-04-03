#ifndef DEVICEHUB_H
#define DEVICEHUB_H

#include "mosquittopp.h"
#include <uuid/uuid.h>
#include <stdint.h>
#include <iostream>
#include <map>
#include <list>
#include <time.h>
#include <chrono>
#include <functional>

using namespace std;

namespace devicehub {

    typedef uuid_t device_uuid_t;
    typedef uuid_t api_key_t;
    typedef uint64_t project_id_t;

    class DeviceHub : public mosqpp::mosquittopp {
    public:
        DeviceHub(project_id_t project_id, device_uuid_t device_id, api_key_t api_key);
        ~DeviceHub();
        void connect(const char * hostname = "io.dev.devicehub.net", unsigned int port = 1883, unsigned int keepalive = 60);
        void autoconfigure();
        void disconnect();
        void send();
        void addSensor(std::string name, std::string type);
        void addActuator(std::string name, std::function <void(int val)> f);
        void addValue(std::string name, double value);
        void listValues(std::string sensor_name);
        void on_connect(int rc);
        void on_message(const struct mosquitto_message *message);
        void on_subscribe(int mid, int qos_count, const int *granted_qos);
        void on_publish();
        enum sensorTypes {
            NUMERIC = 0,
            DIGITAL
        };

    private:
        std::map<std::string, std::map<chrono::milliseconds, double>> sensorList;
        std::map<std::string, std::map<chrono::milliseconds, double>>::iterator sensorListIterator;
        std::map<std::string, int> actuatorList;
        api_key_t api_key;
        project_id_t project_id;
        device_uuid_t device_id;
    };
}

#endif // DEVICEHUB_H
