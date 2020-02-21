/*
 *  Project: ros_redirect
 *  File: time.cpp
 *
 *  Date: 21.02.2020
 *  Author: Markovvn1
 */

#include "time.hpp"

#include <ctime>

uint64_t getCTimeMicrosecond()
{
	timespec time;
	clock_gettime(CLOCK_REALTIME, &time);
	return (uint64_t)(time.tv_sec) * 1000000 + time.tv_nsec / 1000;
}
