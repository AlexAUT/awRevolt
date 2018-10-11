#pragma once

#include <chrono>

namespace aw
{
typedef std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint;
typedef std::chrono::duration<float> Seconds;
typedef std::chrono::duration<float, std::milli> MilliSeconds;
typedef std::chrono::duration<float, std::micro> MicroSeconds;
typedef std::chrono::duration<float, std::nano> NanoSeconds;
} // namespace aw
