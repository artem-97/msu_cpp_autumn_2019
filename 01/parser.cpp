#include "parser.h"

Parser::Parser(Lexer l) : lexer(l), current_token(lexer.get_next_token()){};

void Parser::err() { std::cout << "Could not parse\n"; }

void Parser::eat(const Type &expected) {
  if (current_token.type == expected) {
    current_token = lexer.get_next_token();
  } else {
    err();
  }
}

AST_node *Parser::factor() {
  Token curr = current_token;
  if (current_token.type == Type::INTEGER) {
    eat(Type::INTEGER);
    AST_node *res = new AST_node(curr);
    return res;
  } else if (current_token.type == Type::LP) {
    eat(Type::LP);
    AST_node *node = expr();
    eat(Type::RP);
    return node;
  } else if (current_token.type == Type::PLUS) {
    eat(Type::PLUS);
    AST_node *res = new AST_node(curr);
    res->left = factor();
    res->isUnary = true;
    return res;
  } else if (current_token.type == Type::MINUS) {
    eat(Type::MINUS);
    AST_node *res = new AST_node(curr);
    res->left = factor();
    res->isUnary = true;
    return res;
  }
  return nullptr;
}

AST_node *Parser::term() {
  AST_node *node = new AST_node(current_token);
  node = factor();

  while (current_token.type == Type::MUL || current_token.type == Type::DIV) {
    Token curr = current_token;
    if (curr.type == Type::MUL) {
      eat(Type::MUL);
    } else if (curr.type == Type::DIV) {
      eat(Type::DIV);
    }

    AST_node *tmp = new AST_node(current_token);
    tmp->left = node;
    tmp->right = factor();
    tmp->token = curr;
    node = tmp;
  }

  return node;
}

AST_node *Parser::expr() {
  AST_node *node = new AST_node(current_token);
  node = term();

  while (current_token.type == Type::PLUS ||
         current_token.type == Type::MINUS) {
    Token token = current_token;
    if (current_token.type == Type::PLUS)
      eat(Type::PLUS);
    else if (current_token.type == Type::MINUS)
      eat(Type::MINUS);
    AST_node *tmp = new AST_node(token);
    tmp->left = node;
    tmp->right = term();
    node = tmp;
  }

  return node;
}

AST_node *Parser::parse() { return expr(); }

void Parser::mem_free(AST_node *root) {
  if (root == nullptr) {
    return;
  }
  Parser::mem_free(root->left);
  Parser::mem_free(root->right);
  delete root;
}

Parser::~Parser() {
  AST_node *root = expr();
  Parser::mem_free(root);
}
