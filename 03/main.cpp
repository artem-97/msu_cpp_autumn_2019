#include "matrix.h"
#include <cassert>

int main() {

  Matrix n(12, 2);
  auto y = n[2];
  n[3][1] = 100;
  // std::cout << n;
  const size_t rows = 5;
  const size_t cols = 3;

  Matrix m(rows, cols);

  assert(m.getRows() == 5);
  assert(m.getColumns() == 3);

  m[1][2] = 5; // строка 1, колонка 2
  int x = m[4][1];

  m *= 3; // умножение на число
  Matrix m1(rows, cols);
  Matrix n1(rows, cols);

  m1[2][3] = 5;
  m1[4][2] = 12;

  n1[2][3] = 5;
  n1[4][2] = 12;
  std::cout << m1;
  bool e = (m1[2] == n1[2]);

  if (m1 == n1) {
    std::cout << "eq:\n"
              << "m1:\n"
              << m1 << "----\n"
              << "n1:\n"
              << n1;
  }
}
