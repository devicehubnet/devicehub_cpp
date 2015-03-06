#include <iostream>
#include <chrono>
#include <ctime>
#include <devicehub.h>

#define DEVICE_ID   18
#define API_KEY     123456789

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

int main() {

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

    return 0;
}
