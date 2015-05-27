#include <iostream>
#include <chrono>
#include <ctime>
#include <unistd.h>
#include <devicehub.h>
#include <random>

using namespace std;
using namespace devicehub;

// Project API key
api_key_t     myApiKey    = "c0240384-6430-494b-ad7c-a2d4e2827630";
// Project ID
project_id_t  myProjectId = 313;
// Device UUID
device_uuid_t myDeviceId  = "9c7ea605-bdce-4ec4-b57f-214020c9166f";

bool run = true;

int main() {
    int rc = 0;
    std::random_device rd;

    auto func = [] () { cout << "Hello world"; };

    DeviceHub dh(myProjectId, myDeviceId, myApiKey);

    dh.connect();

    dh.addSensor("temperature", "analog");
    dh.addSensor("humidity", "analog");

    dh.addActuator("Main_Room_Lights", [] (int val) -> void {
            clog<<"something"<<endl;

    });

//    dh.listValues("temperature");
//    dh.listValues("humidity");

    while(run) {
        // Do something useful here
        usleep(100);

        dh.addValue("temperature", std::rand());
        dh.addValue("humidity", std::rand());
        dh.send();
        usleep(1000000);
    }

    return 0;
}
