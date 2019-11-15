#pragma once

#include "vector.h"

#include <cassert>
#include <iostream>

class BigInt {
public:
  // Constructors
  BigInt(int);
  BigInt(Vector, bool);
  BigInt(const BigInt &b);

  // Operator=
  BigInt &operator=(BigInt);
  BigInt &operator=(int);

  // Unary
  BigInt operator-() const;

  // Adding
  BigInt operator+(BigInt const &) const;
  BigInt &operator+=(BigInt const &);

  BigInt operator+(int) const;
  BigInt &operator+=(int);

  // Subtraction
  friend Vector sub(const BigInt &, const BigInt &);
  BigInt operator-(BigInt const &) const;
  BigInt &operator-=(BigInt const &);

  BigInt operator-(int) const;
  BigInt &operator-=(int);

  // Multiplication
  BigInt operator*(BigInt const &);
  BigInt &operator*=(BigInt const &);

  // Compare
  bool operator<(const BigInt &) const;
  bool operator>(const BigInt &) const;
  bool operator<=(const BigInt &) const;
  bool operator>=(const BigInt &) const;
  bool operator==(const BigInt &) const;
  bool operator!=(const BigInt &) const;

  // Output
  friend std::ostream &operator<<(std::ostream &, const BigInt &);

  // Utility
  int compare(const BigInt &) const;
  friend void swap(BigInt &, BigInt &);
  bool is_positive() const;
  bool is_null() const;

private:
  Vector val;
  bool positive = true;
};
