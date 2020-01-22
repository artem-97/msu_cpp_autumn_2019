#pragma once

#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <thread>
#include <vector>

class ThreadPool {
  std::vector<std::thread> workers;
  std::queue<std::function<void()>> tasks;

  std::mutex m;
  std::condition_variable condition;
  bool stop;

public:
  explicit ThreadPool(size_t);
  template <class Func, class... Args>
  auto exec(Func &&f, Args &&... args) -> std::future<decltype(f(args...))>;
  ~ThreadPool();
};

#include "pool.hpp"
