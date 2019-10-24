#pragma once

#include <iostream>
#include <memory>

#include "ast.h"
#include "lexer.h"
#include "token.h"
class Parser {
public:
  explicit Parser(const Lexer &);
  Parser &operator=(const Parser &other) = delete;

  void err();
  void eat(const Type &);
  std::shared_ptr<AST_node> factor();
  std::shared_ptr<AST_node> term();
  std::shared_ptr<AST_node> expr();
  std::shared_ptr<AST_node> parse();

private:
  Lexer lexer;
  Token current_token;
};
