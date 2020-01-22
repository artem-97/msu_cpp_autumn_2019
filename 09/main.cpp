#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

constexpr size_t MEM = 1024 * 1000;

std::vector<std::string> split(std::ifstream &f, uint64_t *buf) {
  size_t idx;

  f.seekg(0, f.end);
  size_t len = f.tellg() / sizeof(uint64_t);
  f.seekg(0, f.beg);

  size_t n_amo = ((size_t)ceil((float)len / MEM)) << 1;

  std::vector<std::string> names(n_amo);
  for (size_t i = 0; i < n_amo; ++i) {
    names[i] = std::to_string(i);
  }

  while (!f.eof()) {
    f.read(reinterpret_cast<char *>(buf), MEM * sizeof(uint64_t));
    size_t read_sz = f.gcount() / sizeof(uint64_t);

    std::thread t1([buf, read_sz]() { std::sort(buf, buf + read_sz / 2); });

    std::thread t2(
        [buf, read_sz]() { std::sort(buf + read_sz / 2, buf + read_sz); });
    t1.join();
    t2.join();

    std::ofstream f1(names[idx], std::ios::binary);
    if (!f1) {
      throw std::ofstream::failure(names[idx]);
    }

    std::ofstream f2(names[idx + 1], std::ios::binary);
    if (!f2) {
      throw std::ofstream::failure(names[idx + 1]);
    }

    f1.write(reinterpret_cast<const char *>(buf),
             sizeof(uint64_t) * read_sz / 2);
    f2.write(reinterpret_cast<const char *>(buf + read_sz / 2),
             sizeof(uint64_t) * read_sz / 2);
    f1.close();
    f2.close();
    idx += 2;
  }
  f.close();
  return names;
}

void merge(std::vector<std::string> &names, uint64_t *buf) {
  for (size_t i = 0; i < names.size() - 1; ++i) {
    std::ifstream f1(names[i], std::ios::binary);
    if (!f1) {
      throw(std::ifstream::failure(names[i]));
    }

    std::ifstream f2(names[i + 1], std::ios::binary);
    if (!f2) {
      throw(std::fstream::failure(names[i + 1]));
    }

    uint64_t cur;
    size_t idx = 0;

    f1.read(reinterpret_cast<char *>(&cur), sizeof(uint64_t));
    f2.seekg(0, f2.end);
    size_t len = f2.tellg() / sizeof(uint64_t);
    f2.seekg(0, f2.beg);
    f2.read(reinterpret_cast<char *>(buf), len * sizeof(uint64_t));
    f2.close();

    std::ofstream f2_o(names[i + 1], std::ios::binary);

    while (idx < len && !f1.eof()) {
      if (cur >= buf[idx]) {
        f2_o.write(reinterpret_cast<const char *>(&buf[idx]), sizeof(uint64_t));
        ++idx;
      }
      if (cur <= buf[idx]) {
        f2_o.write(reinterpret_cast<const char *>(&cur), sizeof(uint64_t));
        f1.read(reinterpret_cast<char *>(&cur), sizeof(uint64_t));
      }
    }

    if (f1.eof())
      f2_o.write(reinterpret_cast<const char *>(&buf[idx]),
                 sizeof(uint64_t) * (len - idx));
    while (!f1.eof()) {
      f2_o.write(reinterpret_cast<const char *>(&cur), sizeof(uint64_t));
      f1.read(reinterpret_cast<char *>(&cur), sizeof(uint64_t));
    }
    f1.close();
    f2_o.close();
  }
}

void clean(std::vector<std::string> &names) {
  std::for_each(names.begin(), names.end() - 1,
                [](std::string &name) { remove(name.c_str()); });
  rename(names.back().c_str(), "res");
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Incorrect input.\n";
    return 1;
  }

  std::ifstream input(argv[1], std::ios::binary);
  if (!input) {
    std::cout << "IO error.\n";
    return 1;
  }
  uint64_t *buf = new uint64_t[MEM];
  try {
    std::vector<std::string> names = split(input, buf);
    merge(names, buf);
    clean(names);
  } catch (std::exception &e) {
    std::cout << e.what() << '\n';
    delete[] buf;
    return 1;
  }
  delete[] buf;
  return 0;
}
