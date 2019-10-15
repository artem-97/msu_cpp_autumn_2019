#pragma once

#include <iostream>

#include "ast.h"
#include "lexer.h"
#include "token.h"
class Parser {
 public:
  Parser(Lexer);
  ~Parser();
  Parser& operator=(const Parser& other) = delete;

  void err();
  void eat(const Type&);
  AST_node* factor();
  AST_node* term();
  AST_node* expr();
  AST_node* parse();

 private:
  Lexer lexer;
  Token current_token;
  void mem_free(AST_node*);
};