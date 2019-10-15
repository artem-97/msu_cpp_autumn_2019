#include "ast.h"

AST_node::AST_node(link left, link right, Token token, bool isUnary) : 
  left(left), right(right), token(token), isUnary(isUnary) {};

AST_node::AST_node(Token token) : token(token) {};
AST_node::AST_node(Token token, bool isUnary) : token(token), isUnary(isUnary) {};
