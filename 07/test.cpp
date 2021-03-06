#include <chrono>
#include <deque>
#include <iostream>
#include <list>
#include <vector>

#include "vector.h"

template <class X, class Y>
void doCheckEqual(const X &actual, const Y &expected, size_t line) {
  if (actual != expected) {
    std::cout << "at line " << line << ": " << actual << " != " << expected
              << '\n';
  }
}

#define checkEqual(x, y)                                                       \
  do {                                                                         \
    doCheckEqual((x), (y), __LINE__);                                          \
  } while (0)
#define checkTrue(cond)                                                        \
  do {                                                                         \
    if (!(cond))                                                               \
      std::cout << "at line " << __LINE__ << ": " << #cond << '\n';            \
  } while (0)

int main() {
  Vector<int> v;

  checkTrue(v.empty());
  checkEqual(v.size(), 0);

  v.push_back(1);

  checkTrue(!v.empty());
  checkEqual(v.size(), 1);
  checkEqual(v[0], 1);

  v.pop_back();

  checkTrue(v.empty());
  checkEqual(v.size(), 0);

  v.push_back(3);
  v.push_back(2);
  v.push_back(1);

  checkTrue(!v.empty());
  checkEqual(v.size(), 3);
  checkEqual(v[0], 3);
  checkEqual(v[1], 2);
  checkEqual(v[2], 1);

  auto r = v.rbegin();
  checkTrue(r != v.rend());
  checkEqual(*r, 1);
  ++r;
  checkTrue(r != v.rend());
  checkEqual(*r, 2);
  ++r;
  checkTrue(r != v.rend());
  checkEqual(*r, 3);
  ++r;
  checkTrue(r == v.rend());

  auto f = v.begin();
  checkTrue(f != v.end());
  checkEqual(*f, 3);
  ++f;
  checkTrue(f != v.end());
  checkEqual(*f, 2);
  ++f;
  checkTrue(f != v.end());
  checkEqual(*f, 1);
  ++f;
  checkTrue(f == v.end());

  v.reserve(10000);
  checkEqual(v.size(), 3);
  checkTrue(v.capacity() >= 10000);

  const auto c = v.capacity();

  v.resize(2);
  checkEqual(v.size(), 2);
  checkEqual(v.capacity(), c);
  checkEqual(v[0], 3);
  checkEqual(v[1], 2);

  v.resize(3);
  checkEqual(v.size(), 3);
  checkEqual(v.capacity(), c);
  checkEqual(v[0], 3);
  checkEqual(v[1], 2);
  checkEqual(v[2], 0);

  v.resize(0);
  checkEqual(v.size(), 0);
  checkTrue(v.begin() == v.end());

  v.resize(2);
  checkEqual(v.size(), 2);
  checkEqual(v[0], 0);
  checkEqual(v[1], 0);

  v.resize(100);

  for (int i = 0; i < 100; ++i) {
    v.push_back(random());
  }

  v.resize(150);

  for (int i = 0; i < 100; ++i) {
    v.pop_back();
  }

  v.resize(25);
  v.clear();

  std::cout << "PASSED\n";
}
