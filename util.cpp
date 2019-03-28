#include "util.h"

namespace Mini
{

std::chrono::milliseconds GetCurrentTimeMS()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
}

std::chrono::nanoseconds GetCurrentTimeNS()
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
}

std::chrono::nanoseconds GetPassedTimeNS()
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startedTimeNS);
}

}