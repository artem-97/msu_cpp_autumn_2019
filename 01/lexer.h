#pragma once

#include <string>
#include <iostream>
#include "token.h"
#include "lexer.h"

class Lexer {
 public:
  Lexer();
  void err() const;
  Token get_next_token();
  int expr();
 private:
  std::string text;
  size_t pos = 0;
  char curr_char;
};