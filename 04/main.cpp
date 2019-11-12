#include <algorithm>
#include <cassert>
#include <iostream>

class Vector {
public:
  explicit Vector(int size)
      : val_(new int[2 * size]), size_(size), capacity_(2 * size) {
    assert(size_ != 0);
  };
  Vector() : val_(new int[10]), size_(0), capacity_(10){};

  Vector(const Vector &v) {
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
  // Vector& operator=(const Vector& v){
  //}

  int size() const { return size_; }

  void push_back(int e) {
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

  int *begin() const {
    // assert(size_ != 0);
    return val_;
  }

  int *end() const {
    // assert(size_ != 0);
    return val_ + size_;
  }

  void reverse() {
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

  int operator[](int i) const {
    assert(i < size_);
    return val_[i];
  }
  int &operator[](int i) {
    assert(i < size_);
    return val_[i];
  }
  friend std::ostream &operator<<(std::ostream &out, const Vector &v);

  ~Vector() {
    assert(val_ != 0);
    delete[] val_;
  }

private:
  int *val_ = nullptr;
  int size_ = 0;
  int capacity_ = 0;
};

std::ostream &operator<<(std::ostream &out, const Vector &v) {
  for (int *it = v.begin(); it != v.end(); ++it) {
    std::cout << *it << ' ';
  }
  return out;
}

class BigInt {
public:
  explicit BigInt(int a) {
    if (a == 0) {
      val.push_back(0);
      return;
    }

    positive = true ? a > 0 : false;

    if (!positive) {
      a *= -1;
    }
    // 3425
    // 342 | 5
    // 34 | 5 2
    // 3 | 5 2 4
    // 5 2 4 3
    // reverse() -> 3 4 2 5
    while (a) {
      int last = a % 10;
      val.push_back(last);
      a /= 10;
    }
    val.reverse();
  };

  BigInt(Vector v, bool pos) : val(v), positive(pos){};

  friend const BigInt operator+(const BigInt &left, const BigInt &right);
  friend bool operator<(const BigInt &left, const BigInt &right);

  virtual ~BigInt() {}
  friend std::ostream &operator<<(std::ostream &out, const BigInt &b);
  bool is_positive() const { return positive; }

  bool is_null() const { return val.size() == 1 && val[0] == 0; }

private:
  Vector val;
  bool positive = true;
};

bool operator<(const BigInt &left, const BigInt &right) {

  // compare with zero
  // left is zero
  if (left.is_null()) {
    if (right.is_null())
      return false;
    else if (right.is_positive())
      return true;
    else {
      assert(!right.is_positive());
      return false;
    }
  }

  // right is zero
  if (right.is_null()) {
    if (left.is_positive()) {
      return false;
    } else {
      assert(!left.is_null() && !left.is_positive());
      return true;
    }
  }

  bool lpos = left.is_positive();
  bool rpos = right.is_positive();

  // both non zeros
  if (lpos && !rpos)
    return false;
  if (!lpos && rpos)
    return true;
  if (lpos && rpos) {
    if (left.val.size() > right.val.size())
      return false;
    if (left.val.size() < right.val.size())
      return true;
    assert(left.val.size() == right.val.size());
    int i = 0;
    bool equal = true;
    while (i < left.val.size()) {
      if (left.val[i] > right.val[i])
        return false;
      if (left.val[i] < right.val[i])
        equal = false;
      ++i;
    }
    return equal == true ? false : true;
  }
  if (!lpos && !rpos) {
    if (left.val.size() > right.val.size())
      return true;
    if (left.val.size() < right.val.size())
      return false;
    assert(left.val.size() == right.val.size());
    int i = 0;
    bool equal = true;
    while (i < left.val.size()) {
      if (left.val[i] > right.val[i])
        return true;
      if (left.val[i] < right.val[i])
        equal = false;
      ++i;
    }
    return equal == true ? false : true;
  }
  return false;
};

const BigInt operator+(const BigInt &left, const BigInt &right) {
  Vector res;
  bool lpos = left.is_positive();
  bool rpos = right.is_positive();

  Vector l = left.val;
  Vector r = right.val;
  if (lpos && rpos) {
    int i = l.size() - 1;
    int j = r.size() - 1;

    int carry = 0;
    while (i >= 0 && j >= 0) {
      int tmp = l[i] + r[j] + carry;
      carry = tmp / 10;
      tmp %= 10;
      res.push_back(tmp);
      --i;
      --j;
    }
    if (i < 0) {
      while (j >= 0) {
        int tmp = carry + r[j];
        carry = tmp / 10;
        tmp %= 10;
        res.push_back(tmp);
        --j;
      }
      res.reverse();
      return BigInt(res, true);
    }
    if (j < 0) {
      while (i >= 0) {
        int tmp = carry + l[j];
        carry = tmp / 10;
        tmp %= 10;
        res.push_back(tmp);
        --i;
      }
      res.reverse();
      return BigInt(res, true);
    }
  }
  return BigInt(res, true);
};

std::ostream &operator<<(std::ostream &out, const BigInt &b) {
  if (!b.positive) {
    std::cout << '-';
  }
  std::cout << b.val;
  return out;
}

int main() {
  BigInt a(425);
  BigInt b(3425);
  std::cout << a + b;
}
