#include <iostream>
#include <chrono>
#include <ctime>
#include <unistd.h>
#include <devicehub.h>
#include <random>

using namespace std;
using namespace devicehub;

// Project API key
api_key_t     myApiKey    = "a8b274d9-4484-4103-8214-e6db353abbd9";
// Project ID
project_id_t  myProjectId = 235;
// Device UUID
device_uuid_t myDeviceId  = "887ffe97-0719-4562-94db-91a86e2e7c49";

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
