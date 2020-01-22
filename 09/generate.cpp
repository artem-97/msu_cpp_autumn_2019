#include <fstream>
#include <iostream>

int main() {
  std::ofstream f("input", std::ios::binary);
  for (size_t i; i < 8 * (1 << 20); ++i) {
    uint64_t x = rand();
    f.write(reinterpret_cast<const char *>(&x), sizeof(uint64_t));
  }
  f.close();
  return 0;
}
