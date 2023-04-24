#pragma once

#include <chrono>
#include <iostream>
#include <utility>
#include <vector>


typedef std::pair<int, int>					iPair;
typedef std::chrono::high_resolution_clock	Clock;
typedef std::chrono::duration<double>		Seconds;


template <typename T>
std::ostream& operator<< (std::ostream& os, const std::vector<T>& v)
{
	auto it = v.begin(), end = v.end();
	os << "[";
	if (it != end) {
		os << *it;
		for (++it; it != end; ++it) {
			os << ", " << *it;
		}
	}
	return os << "]";
}


template <typename Time>
Seconds::rep difftime(Time start, Time end)
{
	return std::chrono::duration_cast<Seconds>(end - start).count();
}

