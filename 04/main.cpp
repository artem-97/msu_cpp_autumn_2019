#include "bigint.h"

#include <cassert>
#include <iostream>

int main() {
  BigInt a1(-4215);
  BigInt b1(-42);
  auto s = (a1 - b1);
  std::cout << s << '\n';

  BigInt a = 1;
  std::cout << "a:" << a << '\n';
  BigInt b = a;
  assert(a == b);

  BigInt c = a + b + 2;
  assert(c == BigInt(4));
  std::cout << "c:" << c << '\n';
}
