#include "matrix.h"

//#include <vector>

Matrix::Matrix(size_t rows, size_t cols)
    : rows_(rows), cols_(cols), M(rows * cols, 0) {}

const size_t Matrix::getRows() const { return rows_; }
const size_t Matrix::getColumns() const { return cols_; }

Matrix &Matrix::operator=(const Matrix &m) {
  if (this == &m) {
    return *this;
  }
  M = m.M;
  rows_ = m.rows_;
  cols_ = m.cols_;

  return *this;
}

Matrix &Matrix::operator*=(int c) {
  for (size_t i = 0; i < rows_ * cols_; ++i) {
    M[i] *= c;
  }
  return *this;
}

bool operator==(const Matrix &left, const Matrix &right) {
  if (left.rows_ != right.rows_ || left.cols_ != right.cols_)
    return false;
  for (size_t i = 0; i < left.rows_ * left.cols_; ++i) {
    if (left.M[i] != right.M[i])
      return false;
  }
  return true;
}

bool operator!=(const Matrix &left, const Matrix &right) {
  return !(left == right);
}
std::ostream &operator<<(std::ostream &out, const Matrix &m) {
  for (size_t i = 0; i < m.rows_ * m.cols_; i++) {
    if ((i + 1) % m.cols_ == 0) {
      std::cout << m.M[i] << '\n';
    } else {
      std::cout << m.M[i] << ' ';
    }
  }
  return out;
}

Matrix::Row Matrix::operator[](size_t i) {
  if (this->rows_ < i)
    throw std::out_of_range("idx error");

  // std::vector<int> M(this->M);
  auto begin = (this->M).begin() + this->cols_ * i;
  auto end = begin + this->cols_;
  return Matrix::Row(begin, end);
}

std::ostream &operator<<(std::ostream &out, const Matrix::Row &r) {
  for (auto it = r.begin; it != r.end; ++it)
    std::cout << *it << ' ';
  // std::cout << "Elements in row: " << r.end - r.begin << '\n';
  return out;
}

int &Matrix::Row::operator[](size_t j) {
  if (this->end - this->begin < j)
    throw std::out_of_range("idx error");
  return *(this->begin + j);
}
