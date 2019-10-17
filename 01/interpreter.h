#pragma once

#include <cstdio>
#include <iostream>
#include <memory>

#include "ast.h"
#include "parser.h"

class Interpreter {
public:
  Interpreter(Parser);
  int visit(std::shared_ptr<AST_node>);
  int interpret();
  void print_AST(std::shared_ptr<AST_node>);

private:
  Parser parser;
};
