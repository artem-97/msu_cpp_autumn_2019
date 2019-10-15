#include "timer.h"

Timer::Timer() : start_(clock_t::now()){};

Timer::~Timer() {
  const auto finish = clock_t::now();
  const auto us =
      std::chrono::duration_cast<microseconds>(finish - start_).count();
  std::cout << us << " us" << std::endl;
}
