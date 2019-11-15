#include "bigint.h"
#include "vector.h"

#include <algorithm>
#include <cassert>
#include <iostream>

// Constructors
BigInt::BigInt(int a) {
  if (a == 0) {
    val.push_back(0);
    return;
  }

  positive = true ? a > 0 : false;

  if (!positive) {
    a *= -1;
  }
  while (a) {
    int last = a % 10;
    val.push_back(last);
    a /= 10;
  }
  val.reverse();
};

BigInt::BigInt(Vector v, bool pos) : val(v), positive(pos){};

BigInt::BigInt(const BigInt &b) : val(b.val), positive(b.positive) {}

// Operator=
BigInt &BigInt::operator=(BigInt b) {
  swap(*this, b);
  return *this;
}

BigInt &BigInt::operator=(int b) {
  auto x = BigInt(b);
  swap(*this, x);
  return *this;
}
// Unary
BigInt BigInt::operator-() const {
  BigInt res(*this);
  res.positive = !this->positive;
  return res;
}

// Adding
BigInt &BigInt::operator+=(const BigInt &b) {
  if (!b.positive) {
    return *this -= b;
  }
  Vector res;
  int i = val.size() - 1;
  int j = b.val.size() - 1;
  int carry = 0;
  while (i >= 0 && j >= 0) {
    int sum = carry + val[i] + b.val[j];
    res.push_back(sum % 10);
    carry = sum / 10;
    --i;
    --j;
  }
  if (i < 0) {
    while (j >= 0) {
      int sum = carry + b.val[j];
      res.push_back(sum % 10);
      carry = sum / 10;
      --j;
    }
  }
  if (j < 0) {
    while (i >= 0) {
      int sum = carry + val[i];
      res.push_back(sum % 10);
      carry = sum / 10;
      --i;
    }
  }
  res.reverse();
  val = res;
  return *this;
}

BigInt BigInt::operator+(const BigInt &b) const {
  BigInt res = *this;
  res += b;
  return res;
}

BigInt &BigInt::operator+=(int b) {
  auto tmp = BigInt(b);
  (*this) += tmp;
  return *this;
}

BigInt BigInt::operator+(int b) const {
  auto tmp = BigInt(b);
  BigInt sum = tmp + *(this);
  return sum;
}

// Subtraction
Vector sub(const BigInt &lhs, const BigInt &rhs) {
  // l - r, l > r
  auto l = lhs.val;
  auto r = rhs.val;

  int i = l.size() - 1;
  int j = r.size() - 1;
  assert(i >= j); // l > r

  Vector res;
  while (i >= 0) {
    int dif;
    if (j >= 0) {
      dif = l[i] - r[j];
      if (l[i] < r[j]) {
        --l[i - 1];
        dif += 10;
      }
      --j;
    } else {
      dif = l[i];
    }
    --i;
    res.push_back(dif);
  }
  res.reverse();
  return res;
}

BigInt &BigInt::operator-=(const BigInt &b) {
  // 5596-=43
  // 5596
  //-  43
  //------------
  Vector res;

  if (*this == b) {
    res.push_back(0);
    val = res;
    return *this;
  }
  // both positive
  if (this->positive && b.positive) {
    if (*this > b) {
      this->val = sub(*this, b);
      this->positive = true;
      return *this;
    } else {
      this->val = sub(b, *this);
      this->positive = false;
      return *this;
    }
  }
  // both negative
  if (!this->positive && !b.positive) {
    //-a -= -b
    //-a + b
    auto a = -(*this);
    if (a < b) {
      this->val = sub(b, a);
      this->positive = true;
    } else {
      this->val = sub(a, b);
    }
    return *this;
  }
  // different signs
  if (!this->positive && b.positive) {
    this->positive = true;
    auto tmp = b;
    tmp.positive = true;
    (*this) += tmp;
    this->positive = false;
    return *this;
  }
  if (this->positive && !b.positive) {
    auto tmp = b;
    tmp.positive = true;
    (*this) += tmp;
    return *this;
  }
  return *this;
}

BigInt BigInt::operator-(const BigInt &b) const {
  BigInt res = *this;
  res -= b;
  return res;
}

BigInt &BigInt::operator-=(int b) {
  auto x = BigInt(b);
  *(this) -= x;
  return *this;
}

BigInt BigInt::operator-(int b) const {
  BigInt res = *this;
  auto x = BigInt(b);
  return res - x;
}

// Compare
bool BigInt::operator<(const BigInt &b) const { return compare(b) == -1; }

bool BigInt::operator<=(const BigInt &b) const {
  int res = compare(b);
  return res == 0 || res == -1;
}

bool BigInt::operator>(const BigInt &b) const { return compare(b) == 1; }

bool BigInt::operator>=(const BigInt &b) const {
  int res = compare(b);
  return res == 0 || res == 1;
}

bool BigInt::operator==(const BigInt &b) const { return compare(b) == 0; }

bool BigInt::operator!=(const BigInt &b) const { return !(*this == b); }

// Output
std::ostream &operator<<(std::ostream &out, const BigInt &b) {
  if (!b.val.size())
    return out;
  if (b.is_null()) {
    std::cout << "0";
    return out;
  }
  if (!b.positive) {
    std::cout << '-';
  }
  std::cout << b.val;
  return out;
}

// Utility
void swap(BigInt &left, BigInt &right) {
  std::swap(left.val, right.val);
  std::swap(left.positive, right.positive);
}

bool BigInt::is_positive() const { return positive; }

bool BigInt::is_null() const { return val.size() == 1 && val[0] == 0; }

int BigInt::compare(const BigInt &b) const {
  // return 0, -1, 1
  //        eq, lt, gt
  if (positive && !b.positive)
    return 1;
  if (!positive && b.positive)
    return -1;

  int sign = 1;
  if (!positive && !b.positive)
    sign = -1;

  if (val.size() < b.val.size())
    return -1 * sign;
  if (val.size() > b.val.size())
    return sign;
  assert(val.size() == b.val.size());
  for (int i = val.size() - 1; i > 0; --i) {
    if (val[i] < b.val[i])
      return -1 * sign;
    if (val[i] > b.val[i])
      return sign;
  }
  return 0;
}
