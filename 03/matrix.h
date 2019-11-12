#pragma once

#include <iostream>
#include <memory>
#include <vector>

class Matrix {
public:
  Matrix(size_t, size_t);
  Matrix &operator=(const Matrix &);

  Matrix &operator*=(int);

  const size_t getRows() const;
  const size_t getColumns() const;

  friend bool operator==(const Matrix &left, const Matrix &right);
  friend bool operator!=(const Matrix &left, const Matrix &right);
  friend std::ostream &operator<<(std::ostream &out, const Matrix &m);

private:
  size_t rows_ = 0;
  size_t cols_ = 0;
  std::vector<int> M;

public:
  class Row {
  public:
    Row(std::vector<int>::iterator begin, std::vector<int>::iterator end)
        : begin(begin), end(end){};
    int &operator[](size_t);

    friend std::ostream &operator<<(std::ostream &out, const Row &m);

  private:
    std::vector<int>::iterator begin;
    std::vector<int>::iterator end;
  };

  Row operator[](size_t);
};
