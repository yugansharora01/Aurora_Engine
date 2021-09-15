#include "pch.h"
#include "AuTimer.h"

using namespace std::chrono;

AuTimer::AuTimer()
{
    last = steady_clock::now();
}

float AuTimer::Mark()
{
    const auto old = last;
    last = steady_clock::now();
    const duration<float> frameTime = last - old;
    return frameTime.count();
}

float AuTimer::Peek() const noexcept
{
    return duration<float>(steady_clock::now() - last).count();
}