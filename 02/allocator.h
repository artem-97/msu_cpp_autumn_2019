#pragma once

#include <cstdlib>
#include <iostream>

template <typename T> class LinearAllocator {
public:
  LinearAllocator(size_t);
  T *alloc(size_t size);
  void reset();
  ~LinearAllocator();
  size_t get_ptr() const; // for tests only
private:
  size_t maxSize_;
  T *buffer_ = nullptr;
  size_t ptr_ = 0;
};

template class LinearAllocator<char>;
