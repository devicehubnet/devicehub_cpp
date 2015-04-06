#include <iostream>
#include <chrono>
#include <ctime>
#include <unistd.h>
#include <devicehub.h>
#include <random>

using namespace std;
using namespace devicehub;

#if __cplusplus < 201103L && (!defined(_MSC_VER) || _MSC_VER < 1700)
#error jrd::Timer class requires C++11 support
#else
#include <chrono>
#include <ostream>

namespace jrd {
    namespace time {
        class Timer {
            typedef std::chrono::high_resolution_clock high_resolution_clock;
            typedef std::chrono::milliseconds milliseconds;
        public:
            explicit Timer(bool run = false)
            {
                if (run)
                    Reset();
            }
            void Reset()
            {
                _start = high_resolution_clock::now();
            }
            milliseconds Elapsed() const
            {
                return std::chrono::duration_cast<milliseconds>(high_resolution_clock::now() - _start);
            }
            template <typename T, typename Traits>
            friend std::basic_ostream<T, Traits>& operator<<(std::basic_ostream<T, Traits>& out, const Timer& timer)
            {
                return out << timer.Elapsed().count();
            }
        private:
            high_resolution_clock::time_point _start;
        };
    }
}
#endif

api_key_t     myApiKey    = "a8b274d9-4484-4103-8214-e6db353abbd9";
project_id_t  myProjectId = 235;
device_uuid_t myDeviceId  = "887ffe97-0719-4562-94db-91a86e2e7c49";
bool run = true;

void timer_test() {
    jrd::time::Timer timer(true);
    // Kill some time
    for (int i = 0; i < 1000000000; i++)
        ;
    std::cout << "Elapsed time: " << std::fixed << timer << "ms\n";
    timer.Reset();
    // Kill some more time
    for (int i = 0; i < 10000000; i++)
        ;
    auto elapsed = timer.Elapsed();
    std::cout << "Elapsed time: " << std::fixed << elapsed.count() << "ms\n";
}

int main() {
    int rc = 0;
    std::random_device rd;

    auto func = [] () { cout << "Hello world"; };

    DeviceHub dh(myProjectId, myDeviceId, myApiKey);

    dh.connect();

    dh.addSensor("temperature", "numeric");
    dh.addSensor("humidity", "numeric");

//    dh.addValue("temperature", std::rand());
//    dh.addValue("humidity", std::rand());

    dh.addActuator("Main_Room_Lights", [] (int val) -> void {
            clog<<"something"<<endl;
    });


    dh.send();

    dh.listValues("temperature");
    dh.listValues("humidity");

    while(run) {
        // Do something usefull here
        usleep(100);

        dh.addValue("temperature", std::rand());
        dh.addValue("humidity", std::rand());
        dh.send();
        usleep(1000000);
    }

    return 0;
}
