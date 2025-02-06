#include "helper.h"
#include <cstdio>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

/**
 * @brief Gets the current timestamp with millisecond precision.
 * @return A formatted string containing the current time.
 */
std::string get_timestamp() {
    using namespace std::chrono;
    auto now = system_clock::now();
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
    std::time_t now_time = system_clock::to_time_t(now);
    std::tm local_tm;
#ifdef _WIN32
    localtime_s(&local_tm, &now_time);
#else
    localtime_r(&now_time, &local_tm);
#endif
    std::ostringstream oss;
    oss << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S")
        << '.' << std::setfill('0') << std::setw(3) << ms.count();
    return oss.str();
}

/**
 * @brief Determines whether a number is prime.
 * @param num The number to check.
 * @return true if num is prime, false otherwise.
 */
bool is_prime(int num) {
    if (num <= 1)
        return false;
    for (int i = 2; i <= std::sqrt(num); i++) {
        if (num % i == 0)
            return false;
    }
    return true;
}