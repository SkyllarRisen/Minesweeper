#include "FrameTimer.h"
#include <chrono>

FrameTimer::FrameTimer()
    :m_last(std::chrono::steady_clock::now())
{   
}

double FrameTimer::Mark()
{
    const auto old = m_last;
    m_last = std::chrono::steady_clock::now();
    const std::chrono::duration<double> frameTime = m_last - old;
    return frameTime.count();
}
