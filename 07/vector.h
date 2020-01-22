#pragma once

template <class T> class Allocator {
public:
  T *allocate(size_t);

  void deallocate(T *, size_t);
  void construct(T *, size_t);
  void construct(T *, T);
  void destroy(T *, size_t);
};

template <class T> class Iterator {
public:
  Iterator(T *, bool = true);

  T &operator*() const;

  Iterator &operator+(size_t);
  Iterator &operator++();
  Iterator &operator-(size_t);
  Iterator &operator--();

  bool operator==(const Iterator<T> &) const;
  bool operator!=(const Iterator<T> &) const;

private:
  bool reverse_;
  T *pointer_;
};

template <class T, class Alloc = Allocator<T>> class Vector {
private:
  Alloc alloc_;
  T *pointer_;
  size_t size_;
  size_t capacity_;

  void expand_space(size_t);

public:
  Vector();
  Vector(size_t count);
  ~Vector();

  T &operator[](size_t);

  void push_back(T &&);
  void push_back(const T &);
  void pop_back();
  bool empty();
  size_t size();
  size_t capacity();
  void clear();

  Iterator<T> begin();
  Iterator<T> end();
  Iterator<T> rbegin();
  Iterator<T> rend();

  void resize(size_t);
  void reserve(size_t);
};

#include "vector.hpp"
