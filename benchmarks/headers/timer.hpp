#ifndef _TIMER_
#define _TIMER_

#include <iostream>
#include <chrono>
#include <omp.h>

class Timer {
 private:
  bool strt;  // timer start flag
  bool stp;   // timeк stop flag
  std::chrono::time_point<std::chrono::high_resolution_clock> m_StartPoint{};
  std::chrono::duration<double> duration;

 public:
  Timer();  // сonstructor: initializes the timer duration to zero microseconds
  ~Timer();      // returns a time measurement resource
  void start();  // starts the timer
  void stop();   // stops time

  double duration_s();   // Timer measurement duration in seconds
  double duration_ms();  // Timer measurement duration in milliseconds
};

#endif  // _TIMER_
