/* Example usage:
// Define a function that executes the to be measured time
Timer T;
int a = 0;
T.start();
for(int i = 0; i < 10000; i++){
    a += 2;
}
T.stop();
std::cout << "Program execution time:" << std::endl;
std::cout << T.duration_s() << " seconds" << std::endl;
std::Cout << T.duration_ms() << " milliseconds" << std::endl;

// Examples of Warnings Occurring in Time Measurement
// The time will be measured incorrectly and a warning will be displayed:
// the timer has not been stopped
Timer T;
int a = 0;
T.start();
for(int i = 0; i < 10000; i++){
    a += 2;
}
std::cout << "Program execution time:" << std::endl;
std::cout << T.duration_s() << " seconds" << std::endl;
std::Cout << T.duration_ms() << " milliseconds" << std::endl;
// OUTPUT warning: Warning!!! The timer did not stop 
*/

#ifndef _TIMER_
#define _TIMER_

#include <iostream>
#include <chrono>

class Timer
{
private:
    bool strt;      // timer start flag
    bool stp;       // timeк stop flag
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartPoint{};
    std::chrono::duration<double> duration;
public:
    Timer();                // сonstructor: initializes the timer duration to zero microseconds
    ~Timer();               // returns a time measurement resource
    void start();           // starts the timer
    void stop();            // stops time

    double duration_s();    // Timer measurement duration in seconds
    double duration_ms();   // Timer measurement duration in milliseconds
};

#endif  // _TIMER_