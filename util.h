#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdio.h>
#include <string>
#include <chrono>
#include <ratio>

namespace Mini
{

extern "C" {
    extern std::chrono::time_point<std::chrono::high_resolution_clock> startedTimeNS;
}

std::chrono::milliseconds GetCurrentTimeMS();
std::chrono::nanoseconds GetCurrentTimeNS();
std::chrono::nanoseconds GetPassedTimeNS();

}

#endif // __UTIL_H__