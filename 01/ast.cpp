#include "ast.h"

AST_node::AST_node(link left, link right, const Token &token, bool isUnary)
    : left(left), right(right), token(token), isUnary(isUnary){};

AST_node::AST_node(const Token &token) : token(token){};
AST_node::AST_node(const Token &token, bool isUnary)
    : token(token), isUnary(isUnary){};
