#pragma once


#include <vector>
#include <iostream>
#include <chrono>
#include <string>
#include <utility>
#include <string.h>

typedef std::vector<int>								iVector;
typedef std::vector<double>								dVector;
typedef std::vector<std::vector<double>>				dMatrix;
typedef std::vector<std::vector<std::vector<double>>>	ddMatrix;
typedef std::vector<std::vector<int>>					iMatrix;
typedef std::chrono::high_resolution_clock				Clock;
typedef std::chrono::duration<double>					Seconds;
typedef std::pair <iVector,double> 						fv_obj;

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