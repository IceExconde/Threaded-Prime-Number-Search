#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <cmath>
#include <chrono>
#include <ctime>

/**
 * @brief Gets the current timestamp including milliseconds.
 * @return A string representing the current timestamp in "YYYY-MM-DD HH:MM:SS.mmm" format.
 */
std::string get_timestamp();

/**
 * @brief Checks if a number is prime.
 * @param num The number to check.
 * @return true if the number is prime, false otherwise.
 */
bool is_prime(int num);

#endif // HELPER_H