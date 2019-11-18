#include <cassert>
#include <iostream>
#include <string>

#include "formatter.h"
int main() {
  auto text1 = format("{1}+{1} = {0}", 2, "one");
  assert(text1 == "one+one = 2");
  std::cout << text1 << '\n';

  auto text2 = format("{0} ** {1} = {2}", "2", "ten", 1024);
  std::cout << text2 << '\n';
}
