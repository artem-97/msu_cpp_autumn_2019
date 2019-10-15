#include "timer.h"

const int ZERO = 0;
const int M = 1000;
const int N = 2000;

void fill_rows(int a[], const int M, const int N) {
  Timer t;
  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < N; ++j) {
      a[i * N + j] = ZERO;
    }
  }
}

void fill_cols(int a[], const int M, const int N) {
  Timer t;
  for (int j = 0; j < N; ++j) {
    for (int i = 0; i < M; ++i) {
      a[i * N + j] = ZERO;
    }
  }
}

int main() {
  int *a = new int[M * N];
  fill_cols(a, M, N);
  fill_rows(a, M, N);

  delete[] a;
  return 0;
}
