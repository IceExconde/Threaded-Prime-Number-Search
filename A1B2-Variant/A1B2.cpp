#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <vector>
#include "helper.h"

std::mutex output_mutex;

/**
 * @brief Finds prime numbers using a round-robin approach and prints them immediately.
 * @param start Start value for the thread.
 * @param step Increment step for each iteration.
 * @param range_limit Maximum limit of the range.
 * @param thread_id ID of the thread executing the function.
 */
void find_primes_print_immediately_linear(int start, int step, int range_limit, int thread_id) {
    for (int num = start; num <= range_limit; num += step) {
        if (is_prime(num)) {
            std::lock_guard<std::mutex> lock(output_mutex);
            std::cout << "[Thread " << thread_id << " | " << get_timestamp()
                << "] Prime: " << num << std::endl;
        }
    }
}

int main() {
    int num_threads, range_num;
    std::ifstream config("config.txt");
    if (!config) {
        std::cerr << "Error: Could not open config.txt" << std::endl;
        return 1;
    }
    if (!(config >> num_threads >> range_num)) {
        std::cerr << "Error: Invalid input in config.txt. Expecting two integer values separated by a space." << std::endl;
        return 1;
    }
    if (num_threads <= 0 || range_num <= 0) {
        std::cerr << "Error: Invalid values. num_threads and range_num must be positive integers." << std::endl;
        return 1;
    }
    config.close();

    std::cout << "Execution started at: " << get_timestamp() << std::endl;

    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; i++) {
        threads.push_back(std::thread(find_primes_print_immediately_linear, i + 1, num_threads, range_num, i));
    }

    for (auto& t : threads)
        t.join();

    std::cout << "Execution ended at: " << get_timestamp() << std::endl;

    return 0;
}