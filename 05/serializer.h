#pragma once
#include <iostream>

enum class Error { NoError, CorruptedArchive };

class Serializer {
  static constexpr char Separator = ' ';

public:
  explicit Serializer(std::ostream &);
  template <class T> Error save(T &);
  template <class... Args> Error operator()(Args &&...);

private:
  std::ostream &out_;
  Error save(const bool);

  Error save(const uint64_t);

  template <class T> Error process(T &&);
  template <class T, class... Args> Error process(T &&, Args &&...);
};

class Deserializer {
  static constexpr char Separator = ' ';

public:
  explicit Deserializer(std::istream &);
  template <class T> Error load(T &object);
  template <class... ArgsT> Error operator()(ArgsT &&...);

private:
  std::istream &in_;

  Error load(bool &);
  Error load(uint64_t &);

  template <class T> Error process(T &&val);
  template <class T, class... Args> Error process(T &&, Args &&...);
};

#include "serializer.hpp"
