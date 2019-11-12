#include "matrix.h"

int main() {
  Matrix m(12, 2);
  Matrix n(12, 2);
  auto x = n[2];
  n[3][1] = 100;
  std::cout << n;
}
