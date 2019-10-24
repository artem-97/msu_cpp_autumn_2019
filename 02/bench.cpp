#include <benchmark/benchmark.h>

#include "allocator.cpp"

const size_t MAX_SIZE = 1000'000'000'000'000;
const size_t ONE_ITERATION = 1;

static void BM_LinearAllocator(benchmark::State &state) {
  LinearAllocator<char> allocator(MAX_SIZE);
  for (auto _ : state)
    allocator.alloc(ONE_ITERATION);
}

// Register the function as a benchmark
BENCHMARK(BM_LinearAllocator);

// Define another benchmark
static void BM_Malloc(benchmark::State &state) {
  for (auto _ : state)
    char *ptr = (char *)malloc(ONE_ITERATION);
}
BENCHMARK(BM_Malloc);

BENCHMARK_MAIN();
