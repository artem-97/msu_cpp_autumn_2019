#include "vector.h"

#include <algorithm>
#include <cassert>
#include <iostream>

// Constructors/Destructor
Vector::Vector(int size)
    : val_(new int[2 * size]), size_(size), capacity_(2 * size) {
  assert(size_ != 0);
};

Vector::Vector() : val_(new int[10]), size_(0), capacity_(10){};
Vector::Vector(const Vector &v) {
  size_ = v.size_;
  capacity_ = v.capacity_;
  if (size_ != 0) {
    val_ = new int[size_];
    for (int i = 0; i < v.size(); ++i) {
      val_[i] = v.val_[i];
    }
  } else {
    val_ = new int[10];
    val_[0] = v.val_[0];
  }
}

Vector::~Vector() {
  assert(val_ != 0);
  delete[] val_;
}

// Utility
int Vector::size() const { return size_; }

void swap(Vector &left, Vector &right) {
  std::swap(left.val_, right.val_);
  std::swap(left.size_, right.size_);
  std::swap(left.capacity_, right.capacity_);
}

void Vector::push_back(int e) {
  if (size_ == 0) {
    size_ += 1;
    assert(val_ != nullptr);
    val_[0] = e;
    return;
  }
  if (size_ + 1 > capacity_) { // not enough memory
    int new_size = 2 * size_;
    int *new_val = new int[2 * new_size];
    int new_capacity = 2 * new_size;
    for (int i = 0; i < size_; ++i) {
      new_val[i] = val_[i];
    }
    delete[] val_;
    val_ = new_val;
    size_ = new_size;
    capacity_ = new_capacity;
  } else { // enough memory
    val_[size_] = e;
    size_ += 1;
  }
}

int *Vector::begin() const {
  // assert(size_ != 0);
  return val_;
}

int *Vector::end() const {
  // assert(size_ != 0);
  return val_ + size_;
}

void Vector::reverse() {
  assert(size_ != 0);
  int *begin = this->begin();
  int *end = this->end() - 1;
  while (begin < end) {
    int tmp = *begin;
    *begin = *end;
    *end = tmp;
    ++begin;
    --end;
  }
}

// Operators

Vector &Vector::operator=(Vector v) {
  swap(v, *this);
  return *this;
}

int Vector::operator[](int i) const {
  assert(i < size_);
  return val_[i];
}

int &Vector::operator[](int i) {
  assert(i < size_);
  return val_[i];
}

std::ostream &operator<<(std::ostream &out, const Vector &v) {
  for (int *it = v.begin(); it != v.end(); ++it) {
    std::cout << *it << ' ';
  }
  return out;
}
