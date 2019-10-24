#include <cassert>
#include <iostream>

#include "allocator.cpp"

void test() {
  const size_t N = 10'000;

  LinearAllocator<char> allocator(N);
  size_t curr_ptr = 0;
  auto x = allocator.alloc(0);
  assert(curr_ptr == 0);
  // std::cout << "first: expected 0, got " << allocator.get_ptr() << '\n';

  x = allocator.alloc(10);
  assert(allocator.get_ptr() == 10);
  assert(x != nullptr);

  x = allocator.alloc(1000);
  assert(allocator.get_ptr() == 1000 + 10);
  assert(x != nullptr);

  allocator.reset();
  assert(allocator.get_ptr() == 0);
  assert(x != nullptr);

  allocator.alloc(N + 1);

  {
    LinearAllocator<char> allocator2(N);
    auto y = allocator2.alloc(1000);
    assert(y != nullptr);
  }
}

int main() { test(); }
