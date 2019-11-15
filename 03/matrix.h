#pragma once

#include <iostream>
#include <memory>
#include <vector>

class Matrix {
public:
  // Constructor
  Matrix(size_t, size_t);

  // Operators
  Matrix &operator=(const Matrix &);
  Matrix &operator*=(int);

  // Compare
  bool operator==(const Matrix &) const;
  bool operator!=(const Matrix &) const;

  // Output
  friend std::ostream &operator<<(std::ostream &out, const Matrix &m);

  // Utility
  const size_t getRows() const;
  const size_t getColumns() const;

private:
  size_t rows_ = 0;
  size_t cols_ = 0;
  std::vector<int> M;

public:
  class Row {
  public:
    Row(std::vector<int>::iterator, std::vector<int>::iterator);
    Row(std::vector<int>::const_iterator, std::vector<int>::const_iterator);

    // Operators
    int &operator[](size_t);
    int &operator[](size_t) const;

    // Compare
    bool operator==(const Row &) const;
    bool operator!=(const Row &) const;

    // Output
    friend std::ostream &operator<<(std::ostream &out, const Row &m);

  private:
    std::vector<int>::iterator begin;
    std::vector<int>::iterator end;
  };

  Row operator[](size_t);
  Row operator[](size_t) const;
};
