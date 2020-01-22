#include <sstream>
#include <string>
#include <vector>

std::string format_impl(const std::string &fmt,
                        const std::vector<std::string> &strs) {
  std::string res;
  std::string buf;

  for (int i = 0; i < fmt.length(); ++i) {
    if (fmt[i] == OBRACKET) {
      int j = i + 1;
      while (j < fmt.length() && fmt[j] >= '0' && fmt[j] <= '9') {
        buf += fmt[j];
        ++j;
      }
      if (fmt[j] == CBRACKET) {
        int idx = std::atoi(buf.c_str());
        buf.clear();
        if (idx >= strs.size())
          throw std::runtime_error("Index error.");
        res += strs[idx];
      } else {
        throw std::runtime_error("Bad input. Only {n} expressions allowed.");
      }
      i = j;
    } else {
      res += fmt[i];
    }
  }
  return res;
}

template <typename Arg, typename... Args>
std::string format_impl(const std::string &fmt, std::vector<std::string> &strs,
                        Arg &&arg, Args &&... args) {
  std::stringstream ss;
  ss << arg;
  // strs.push_back(std::forward<std::string>(ss.str()));
  strs.push_back(ss.str());

  return format_impl(fmt, strs, std::forward<Args>(args)...);
}

std::string format(const std::string &fmt) { return fmt; }

template <typename Arg, typename... Args>
std::string format(const std::string &fmt, Arg &&arg, Args &&... args) {
  std::vector<std::string> strs;
  return format_impl(fmt, strs, std::forward<Arg>(arg),
                     std::forward<Args>(args)...);
}
