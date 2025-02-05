#include "helper.h"
#include <cstdio>   
#include <errno.h>  

std::string get_timestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t time_now = std::chrono::system_clock::to_time_t(now);
    char buffer[26]; // Buffer must be at least 26 bytes for ctime_s.
    errno_t err = ctime_s(buffer, sizeof(buffer), &time_now);
    if (err != 0) {
        return "Unknown time";
    }
    std::string timestamp(buffer);
    if (!timestamp.empty() && timestamp.back() == '\n')
        timestamp.pop_back();
    return timestamp;
}

bool is_prime(int num) {
    if (num <= 1)
        return false;
    for (int i = 2; i <= std::sqrt(num); i++) {
        if (num % i == 0)
            return false;
    }
    return true;
}