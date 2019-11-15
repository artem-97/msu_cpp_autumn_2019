#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>

class Vector {
public:
  // Constructors
  explicit Vector(int size);
  Vector();
  Vector(const Vector &);

  // Utility
  friend void swap(Vector &, Vector &);
  int size() const;
  void push_back(int);

  int *begin() const;
  int *end() const;

  void reverse();

  // Operators
  Vector &operator=(Vector);
  int operator[](int) const;
  int &operator[](int);
  friend std::ostream &operator<<(std::ostream &, const Vector &);

  ~Vector();

private:
  int *val_ = nullptr;
  int size_ = 0;
  int capacity_ = 0;
};
