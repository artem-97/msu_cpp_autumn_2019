#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <iostream>

class Timer {
  using clock_t = std::chrono::high_resolution_clock;
  using microseconds = std::chrono::microseconds;

  const clock_t::time_point start_;

public:
  Timer();
  ~Timer();
};

#endif
