#pragma once

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

#include <vector>

constexpr char OBRACKET{'{'};
constexpr char CBRACKET{'}'};

std::string format_impl(const std::string &, const std::vector<std::string> &);

template <typename Arg, typename... Args>
std::string format_impl(const std::string &, std::vector<std::string> &, Arg &&,
                        Args &&...);

template <typename Arg, typename... Args>
std::string format(const std::string &, Arg &&, Args &&...);

std::string format(const std::string &fmt);

#include "formatter.hpp"
