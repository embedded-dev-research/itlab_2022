#ifndef _TIMER_
#define _TIMER_

#include <iostream>
#include <chrono>

class Timer
{
private:
    bool strt = false;
    bool stp = false;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartPoint{};
    std::chrono::duration<double> duration;
public:
    void start();
    void stop();

    double duration_s();
    double duration_ms();
};

#endif