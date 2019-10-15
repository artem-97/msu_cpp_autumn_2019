#pragma once

#include "token.h"
struct AST_node {
  using link = AST_node *;
  link left = nullptr;
  link right = nullptr;
  Token token;
  bool isUnary = false; // does node contain unary plus/minus

  AST_node(link, link, Token, bool);

  AST_node(Token);
  AST_node(Token, bool);
};
