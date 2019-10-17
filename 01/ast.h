#pragma once

#include "token.h"
#include <memory>

struct AST_node {
  using link = std::shared_ptr<AST_node>;
  link left;
  link right;
  Token token;
  bool isUnary = false; // does node contain unary plus/minus

  AST_node(link, link, Token, bool);

  AST_node(Token);
  AST_node(Token, bool);
};
