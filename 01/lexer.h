#pragma once

#include "lexer.h"
#include "token.h"
#include <iostream>
#include <string>

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
