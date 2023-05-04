#include "timer.hpp"

Timer::Timer()
    : strt(true), stp(false), duration(std::chrono::microseconds{0}) {
  start();
}

Timer::~Timer() {
  if (strt && !stp) stop();
}

void Timer::start() {
  strt = true;
  stp = false;
  m_StartPoint = std::chrono::high_resolution_clock::now();
} /*-------------------------------------------------------------------------*/

void Timer::stop() {
  stp = true;
  std::chrono::time_point<std::chrono::high_resolution_clock> m_EndPoint = 
      std::chrono::high_resolution_clock::now();
  duration = m_EndPoint - m_StartPoint;
} /*-------------------------------------------------------------------------*/

double Timer::duration_s() {
  if (!stp) std::cout << "Warning!!! The timer did not stop" << std::endl;
  return duration.count();
} /*-------------------------------------------------------------------------*/

double Timer::duration_ms() {
  if (!stp) std::cout << "Warning!!! The timer did not stop" << std::endl;
  return duration.count() * 1000.0;
} /*-------------------------------------------------------------------------*/
