#include "allocator.h"

template class LinearAllocator<char>;

template <class T>
LinearAllocator<T>::LinearAllocator(size_t maxSize)
    : maxSize_(maxSize), ptr_(0) {
  buffer_ = static_cast<T *>(malloc(maxSize_));
};

template <class T> T *LinearAllocator<T>::alloc(size_t size) {
  if (ptr_ + size > maxSize_) {
    std::cout << "Bad alloc\n";
    return nullptr;
  } else {
    ptr_ += size * sizeof(T);
    return (buffer_ + ptr_ + size * sizeof(T));
  }
};

template <class T> void LinearAllocator<T>::reset() { ptr_ = 0; }

template <class T> LinearAllocator<T>::~LinearAllocator() {
  if (buffer_ != nullptr) {
    delete buffer_;
  }
};

template <class T> size_t LinearAllocator<T>::get_ptr() const {
  return this->ptr_;
}
