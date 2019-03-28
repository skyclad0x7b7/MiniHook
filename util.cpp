#include "util.h"

namespace Mini
{

std::chrono::nanoseconds GetPassedTimeNS()
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startedTimeNS);
}

}