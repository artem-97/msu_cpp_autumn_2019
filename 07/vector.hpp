template <class T> T *Allocator<T>::allocate(size_t n) {
  return (T *)malloc(sizeof(T) * n);
}

template <class T> void Allocator<T>::deallocate(T *ptr, size_t n) {
  free(ptr);
}

template <class T> void Allocator<T>::construct(T *ptr, size_t count) {
  for (size_t i = 0; i < count; ++i) {
    new (ptr + i) T();
  }
}

template <class T> void Allocator<T>::construct(T *ptr, T val) {
  new (ptr) T(val);
}

template <class T> void Allocator<T>::destroy(T *ptr, size_t n) {
  for (size_t i = 0; i < n; ++i) {
    ptr[i].~T();
  }
}

template <class T> Iterator<T>::Iterator(T *ptr, bool reverse) {
  pointer_ = ptr;
  reverse_ = reverse;
}

template <class T> T &Iterator<T>::operator*() const { return *pointer_; }

template <class T> Iterator<T> &Iterator<T>::operator+(size_t count) {
  if (reverse_) {
    pointer_ += count;
  } else {
    pointer_ -= count;
  }

  return *this;
}

template <class T> Iterator<T> &Iterator<T>::operator++() {
  if (reverse_) {
    pointer_++;
  } else {
    pointer_--;
  }

  return *this;
}

template <class T> Iterator<T> &Iterator<T>::operator-(size_t count) {
  if (reverse_) {
    pointer_ -= count;
  } else {
    pointer_ += count;
  }

  return *this;
}

template <class T> Iterator<T> &Iterator<T>::operator--() {
  if (reverse_) {
    pointer_--;
  } else {
    pointer_++;
  }

  return *this;
}

template <class T> bool Iterator<T>::operator==(const Iterator<T> &it) const {
  return pointer_ == it.pointer_;
}

template <class T> bool Iterator<T>::operator!=(const Iterator<T> &it) const {
  return pointer_ != it.pointer_;
}

template <class T, class Alloc>
void Vector<T, Alloc>::expand_space(size_t new_size) {
  auto new_pointer = alloc_.allocate(new_size);

  for (size_t i = 0; i < size_; ++i) {
    alloc_.construct(new_pointer + i, pointer_[i]);
  }

  alloc_.destroy(pointer_, size_);
  alloc_.deallocate(pointer_, capacity_);
  pointer_ = new_pointer;
}

template <class T, class Alloc> Vector<T, Alloc>::Vector() {
  size_ = 0;
  capacity_ = 0;
  pointer_ = nullptr;
}

template <class T, class Alloc> Vector<T, Alloc>::Vector(size_t count) {
  pointer_ = alloc_.allocate(count);
  size_ = 0;
  capacity_ = count;
}

template <class T, class Alloc> Vector<T, Alloc>::~Vector() {
  alloc_.destroy(pointer_, size_);
  alloc_.deallocate(pointer_, capacity_);
}

template <class T, class Alloc> T &Vector<T, Alloc>::operator[](size_t ind) {
  if (ind >= size_ || ind < 0) {
    throw std::out_of_range("Index out of range");
  }

  return pointer_[ind];
}

template <class T, class Alloc> void Vector<T, Alloc>::push_back(T &&val) {
  if (capacity_ == 0) {
    pointer_ = alloc_.allocate(1);
    pointer_[0] = val;
    size_ = 1;
    capacity_ = 1;
  } else if (size_ == capacity_) {
    expand_space(capacity_ * 2);
    pointer_[size_++] = val;
    capacity_ *= 2;
  } else {
    pointer_[size_++] = val;
  }
}

template <class T, class Alloc> void Vector<T, Alloc>::push_back(const T &val) {
  if (capacity_ == 0) {
    pointer_ = alloc_.allocate(1);
    pointer_[0] = val;
    size_ = 1;
    capacity_ = 1;
  } else if (size_ == capacity_) {
    expand_space(capacity_ * 2);
    pointer_[size_++] = val;
    capacity_ *= 2;
  } else {
    pointer_[size_++] = val;
  }
}

template <class T, class Alloc> void Vector<T, Alloc>::pop_back() {
  if (size_ == 0) {
    throw std::runtime_error("Empty vector");
  }

  alloc_.destroy(pointer_ + size_ - 1, 1);
  size_--;
}

template <class T, class Alloc> bool Vector<T, Alloc>::empty() {
  return size_ == 0;
}

template <class T, class Alloc> size_t Vector<T, Alloc>::size() {
  return size_;
}

template <class T, class Alloc> size_t Vector<T, Alloc>::capacity() {
  return capacity_;
}

template <class T, class Alloc> void Vector<T, Alloc>::clear() {
  alloc_.destroy(pointer_, size_);
  size_ = 0;
}

template <class T, class Alloc> Iterator<T> Vector<T, Alloc>::begin() {
  return Iterator<T>(pointer_);
}

template <class T, class Alloc> Iterator<T> Vector<T, Alloc>::end() {
  return Iterator<T>(pointer_ + size_);
}

template <class T, class Alloc> Iterator<T> Vector<T, Alloc>::rbegin() {
  return Iterator<T>(pointer_ + size_ - 1, false);
}

template <class T, class Alloc> Iterator<T> Vector<T, Alloc>::rend() {
  return Iterator<T>(pointer_ - 1, false);
}

template <class T, class Alloc> void Vector<T, Alloc>::resize(size_t new_size) {
  if (new_size < size_) {
    alloc_.destroy(pointer_ + new_size, size_ - new_size);
    size_ = new_size;
  } else if (new_size > size_) {
    if (new_size > capacity_) {
      expand_space(new_size);
      capacity_ = new_size;
    }

    alloc_.construct(pointer_ + size_, new_size - size_);
    size_ = new_size;
  }
}

template <class T, class Alloc>
void Vector<T, Alloc>::reserve(size_t new_capacity) {
  if (new_capacity >= size_ && new_capacity > capacity_) {
    expand_space(new_capacity);
    capacity_ = new_capacity;
  }
};
