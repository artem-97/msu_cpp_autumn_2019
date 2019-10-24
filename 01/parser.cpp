#include "parser.h"

Parser::Parser(const Lexer &l)
    : lexer(l), current_token(lexer.get_next_token()){};

void Parser::err() { std::cout << "Could not parse\n"; }

void Parser::eat(const Type &expected) {
  if (current_token.type == expected) {
    current_token = lexer.get_next_token();
  } else {
    err();
  }
}

std::shared_ptr<AST_node> Parser::factor() {
  Token curr = current_token;
  if (current_token.type == Type::INTEGER) {
    eat(Type::INTEGER);
    std::shared_ptr<AST_node> res = std::make_shared<AST_node>(curr);
    return res;
  } else if (current_token.type == Type::LP) {
    eat(Type::LP);
    std::shared_ptr<AST_node> node = expr();
    eat(Type::RP);
    return node;
  } else if (current_token.type == Type::PLUS) {
    eat(Type::PLUS);
    std::shared_ptr<AST_node> res = std::make_shared<AST_node>(curr);
    res->left = factor();
    res->isUnary = true;
    return res;
  } else if (current_token.type == Type::MINUS) {
    eat(Type::MINUS);
    std::shared_ptr<AST_node> res = std::make_shared<AST_node>(curr);
    res->left = factor();
    res->isUnary = true;
    return res;
  }
  return nullptr;
}

std::shared_ptr<AST_node> Parser::term() {
  std::shared_ptr<AST_node> node = std::make_shared<AST_node>(current_token);
  node = factor();

  while (current_token.type == Type::MUL || current_token.type == Type::DIV) {
    Token curr = current_token;
    if (curr.type == Type::MUL) {
      eat(Type::MUL);
    } else if (curr.type == Type::DIV) {
      eat(Type::DIV);
    }

    std::shared_ptr<AST_node> tmp = std::make_shared<AST_node>(current_token);
    tmp->left = node;
    tmp->right = factor();
    tmp->token = curr;
    node = tmp;
  }

  return node;
}

std::shared_ptr<AST_node> Parser::expr() {
  std::shared_ptr<AST_node> node = std::make_shared<AST_node>(current_token);
  node = term();

  while (current_token.type == Type::PLUS ||
         current_token.type == Type::MINUS) {
    Token token = current_token;
    if (current_token.type == Type::PLUS)
      eat(Type::PLUS);
    else if (current_token.type == Type::MINUS)
      eat(Type::MINUS);
    std::shared_ptr<AST_node> tmp = std::make_shared<AST_node>(token);
    tmp->left = node;
    tmp->right = term();
    node = tmp;
  }

  return node;
}

std::shared_ptr<AST_node> Parser::parse() { return expr(); }
