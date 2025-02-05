#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <algorithm>
#include "helper.h"

void find_primes_store_results_linear(int start, int step, int range_num, std::vector<int>& primes) {
    for (int num = start; num <= range_num; num += step) {
        if (is_prime(num))
            primes.push_back(num);
    }
}

int main() {
    int num_threads, range_limit;
    std::ifstream config("config.txt");
    if (!config) {
        std::cerr << "Error: Could not open config.txt" << std::endl;
        return 1;
    }
    if (!(config >> num_threads >> range_limit)) {
        std::cerr << "Error: Invalid input in config.txt. Expecting two integer values separated by a space." << std::endl;
        return 1;
    }
    if (num_threads <= 0 || range_limit <= 0) {
        std::cerr << "Error: Invalid values. num_threads and range_limit must be positive integers." << std::endl;
        return 1;
    }
    config.close();

    std::cout << "Execution started at: " << get_timestamp() << std::endl;

    std::vector<std::thread> threads;
    std::vector<std::vector<int>> results(num_threads);

    for (int i = 0; i < num_threads; i++) {
        threads.push_back(std::thread(find_primes_store_results_linear, i + 1, num_threads, range_limit, std::ref(results[i])));
    }

    for (auto& t : threads)
        t.join();

    std::vector<int> all_primes;
    for (int i = 0; i < num_threads; i++) {
        all_primes.insert(all_primes.end(), results[i].begin(), results[i].end());
    }

    std::sort(all_primes.begin(), all_primes.end());

    std::cout << "Primes: ";
    for (int prime : all_primes)
        std::cout << prime << " ";
    std::cout << std::endl;

    std::cout << "Execution ended at: " << get_timestamp() << std::endl;

    return 0;
}