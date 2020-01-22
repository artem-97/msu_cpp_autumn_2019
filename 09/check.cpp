#include <algorithm>
#include <fstream>
#include <iostream>

int main() {
  std::ifstream output("res", std::ios::binary);

  output.seekg(0, output.end);
  uint64_t len = output.tellg() / sizeof(uint64_t);
  output.seekg(0, output.beg);

  uint64_t *a = new uint64_t[len + 1];
  output.read(reinterpret_cast<char *>(a), len * sizeof(uint64_t));

  std::cout << (std::is_sorted(a, a + len) ? "File is sorted."
                                           : "File is not sorted.")
            << '\n';
  delete[] a;
  output.close();
  return 0;
}
