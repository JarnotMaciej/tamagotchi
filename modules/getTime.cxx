module;

#include <iostream>
#include <string>
#include <chrono>

export module getTime;

/**
 * @brief Method used for getting time
 * @return time in seconds
 */
export long long int getTime();

long long int getTime()
{
	// to be more precise, this functions gets time in seconds since 1.1.1970
	auto time = std::chrono::system_clock::now();
	auto since_epoch = time.time_since_epoch();
	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(since_epoch);
	return seconds.count();
}