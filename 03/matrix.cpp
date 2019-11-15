#include "matrix.h"

#include <vector>

// Constructors
Matrix::Matrix(size_t rows, size_t cols)
    : rows_(rows), cols_(cols), M(rows * cols, 0) {}

// Operators
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

Matrix::Row Matrix::operator[](size_t i) const {
  if (i >= this->rows_)
    throw std::out_of_range("idx error");

  auto begin = (const_cast<Matrix *>(this)->M).begin() + this->cols_ * i;
  auto end = begin + this->cols_;

  return Matrix::Row(begin, end);
}

Matrix::Row Matrix::operator[](size_t i) {
  if (i >= this->rows_)
    throw std::out_of_range("idx error");

  auto begin = (this->M).begin() + this->cols_ * i;
  auto end = begin + this->cols_;

  return Matrix::Row(begin, end);
}

// Compare
bool Matrix::operator==(const Matrix &other) const {
  if (rows_ != other.rows_)
    return false;
  const Matrix &m = *this;
  for (size_t i = 0; i < rows_; ++i) {
    std::cout << m[i] << '\n';
    if ((*this)[i] != other[i])
      return false;
  }
  return true;
}

// Output
bool Matrix::operator!=(const Matrix &other) const { return !(*this == other); }

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

// Utility
const size_t Matrix::getRows() const { return rows_; }
const size_t Matrix::getColumns() const { return cols_; }

// Row (nested class)
//
// Row Constructors
Matrix::Row::Row(std::vector<int>::iterator begin,
                 std::vector<int>::iterator end)
    : begin(begin), end(end){};

// Row Operators
int &Matrix::Row::operator[](size_t j) {
  if (this->end - this->begin < j)
    throw std::out_of_range("idx error");
  return *(this->begin + j);
}

int &Matrix::Row::operator[](size_t j) const {
  if (this->end - this->begin < j)
    throw std::out_of_range("idx error");
  return *(this->begin + j);
}

// Row Output
std::ostream &operator<<(std::ostream &out, const Matrix::Row &r) {
  for (auto it = r.begin; it != r.end; ++it)
    std::cout << *it << ' ';
  // std::cout << "Elements in row: " << r.end - r.begin << '\n';
  return out;
}

// Row Compare
bool Matrix::Row::operator==(const Matrix::Row &other) const {
  return std::vector<int>(begin, end) ==
         std::vector<int>(other.begin, other.end);
}

bool Matrix::Row::operator!=(const Matrix::Row &other) const {
  return !(*this == other);
}
