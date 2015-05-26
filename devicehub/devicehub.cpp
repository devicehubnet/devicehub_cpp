#include "devicehub.h"
#include <sstream>
#include <string.h>

devicehub::DeviceHub::DeviceHub(project_id_t project_id, device_uuid_t device_id, api_key_t api_key) : mosquittopp() {
    clog<<__FUNCTION__<<endl;
    mosqpp::lib_init();

    strncpy(this->api_key, api_key, sizeof(uuid_string_t));
    this->project_id = project_id;
    strncpy(this->device_id, device_id, sizeof(uuid_string_t));
    connected = false;
}

void devicehub::DeviceHub::connect(const char * hostname, unsigned int port, unsigned int keepalive) {
    clog<<__FUNCTION__<<endl;
    mosqpp::mosquittopp::connect(hostname, port, keepalive);
    loop_start();
}

void devicehub::DeviceHub::autoconfigure() {
    clog<<__FUNCTION__<<endl;
}

void devicehub::DeviceHub::disconnect() {
    clog<<__FUNCTION__<<endl;
}

void devicehub::DeviceHub::on_connect(int rc) {
    clog<<__FUNCTION__<<endl;
    clog<<"Connected with rc "<<rc<<endl;
    if(rc == 0) connected = true;
}

void devicehub::DeviceHub::on_message(const struct mosquitto_message *message) {
    clog<<__FUNCTION__<<endl;
}

void devicehub::DeviceHub::on_subscribe(int mid, int qos_count, const int *granted_qos) {
    clog<<__FUNCTION__<<endl;
    clog<<"Subscribed to topic " << endl;
}

void devicehub::DeviceHub::on_publish() {
    clog<<__FUNCTION__<<endl;
}

void devicehub::DeviceHub::send() {
    clog<<__FUNCTION__<<endl;

    while(!connected);

    for(auto outer_iter=sensorList.begin(); outer_iter!=sensorList.end(); ++outer_iter) {
        for(auto inner_iter=outer_iter->second.begin(); inner_iter!=outer_iter->second.end(); ++inner_iter) {
            clog << "DEBUG: " << outer_iter->first << " " << inner_iter->first.count() << " " << inner_iter->second << endl;
            int mid;
            std::stringstream mqtt_topic;
            std::stringstream mqtt_payload;
            mqtt_topic << "/a/";
            mqtt_topic << api_key;
            mqtt_topic << "/p/";
            mqtt_topic << project_id;
            mqtt_topic << "/device/" << device_id;
            mqtt_topic << "/sensor/" << outer_iter->first;
            mqtt_topic << "/data";

            mqtt_payload << inner_iter->second;

            clog << "DEBUG: MQTT TOPIC: "<< mqtt_topic.str()<<endl;
            publish(&mid, mqtt_topic.str().c_str(), mqtt_payload.str().length(), mqtt_payload.str().c_str());
        }
    }
}

void devicehub::DeviceHub::addSensor(std::string name, std::string type) {
    clog<<__FUNCTION__<<endl;
    std::map<chrono::milliseconds, double> valuesList;
    sensorList.insert ( std::pair<std::string,std::map<chrono::milliseconds, double>>(name, valuesList));
}

void devicehub::DeviceHub::addActuator(std::string name, std::function <void(int val)> f) {
    clog<<__FUNCTION__<<endl;
    int mid;
    std::stringstream mqtt_topic;

    mqtt_topic << "/a/";
    mqtt_topic << api_key;
    mqtt_topic << "/p/";
    mqtt_topic << project_id;
    mqtt_topic << "/device/" << device_id;
    mqtt_topic << "/actuator/" << name;
    mqtt_topic << "/state";

    subscribe(&mid, mqtt_topic.str().c_str());
}

void devicehub::DeviceHub::addValue(std::string name, double value) {
    clog<<__FUNCTION__<<endl;
    sensorListIterator = sensorList.find(name);
    clog<<"found sensor: "<<sensorListIterator->first<<endl;
//    if(it == sensorList.end()) {
//        clog<<__FUNCTION__<<" Could not find coresponding sensor name"<<endl;
//    } else {
//
//    }
    // valuesList.insert ( std::pair<std::string,double>(name, value));
    chrono::milliseconds ms = chrono::duration_cast< chrono::milliseconds >(
            chrono::high_resolution_clock::now().time_since_epoch()
    );
    sensorListIterator->second.insert(std::pair<chrono::milliseconds, double>(ms, value));
}

void devicehub::DeviceHub::listValues(std::string sensor_name) {
    clog<<__FUNCTION__<<" : "<<sensor_name<<endl;
    sensorListIterator = sensorList.find(sensor_name);
    clog<<"found sensor: "<<sensorListIterator->first<<endl;
    for(auto inner_iter=sensorListIterator->second.begin(); inner_iter!=sensorListIterator->second.end(); ++inner_iter) {
        std::cout << "ts: " << inner_iter->first.count() << ", value:" << inner_iter->second << std::endl;
    }

}

devicehub::DeviceHub::~DeviceHub() {
    clog<<__FUNCTION__<<endl;
}
