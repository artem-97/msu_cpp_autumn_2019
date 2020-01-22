#include "pool.h"
#include <iostream>

int main() {
  ThreadPool pool(10);

  for (int i = 0; i < 50; ++i) {
    std::cout << pool.exec([i]() { return i; }).get() << '\n';
  }
}
