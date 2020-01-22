template <class Func, class... Args>
auto ThreadPool::exec(Func &&f, Args &&... args)
    -> std::future<decltype(f(args...))> {
  auto task = std::make_shared<
      std::packaged_task<typename std::result_of<Func(Args...)>::type()>>(
      std::bind(std::forward<Func>(f), std::forward<Args>(args)...));
  auto res = task->get_future();
  {
    std::unique_lock<std::mutex> lock(m);
    if (stop)
      throw std::runtime_error("Already stopped.");
    tasks.emplace([task]() { (*task)(); });
  }
  condition.notify_one();
  return res;
}

ThreadPool::ThreadPool(size_t poolSize) : stop(false) {
  for (size_t i = 0; i < poolSize; ++i)
    workers.emplace_back([this] {
      while (!stop) {
        std::unique_lock<std::mutex> lock(m);
        if (!tasks.empty()) {
          std::function<void()> task = move(tasks.front());
          tasks.pop();
          lock.unlock();
          task();
        } else {
          condition.wait(lock);
        }
      }
    });
}

ThreadPool::~ThreadPool() {
  stop = true;
  condition.notify_all();
  for (std::thread &worker : workers)
    worker.join();
}
