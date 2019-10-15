#pragma once

#include "ast.h"
#include "parser.h"
#include <cstdio>
#include <iostream>

class Interpreter {
public:
  Interpreter(Parser);
  int visit(AST_node *);
  int interpret();
  void print_AST(AST_node *root);

private:
  Parser parser;
};
