#include "interpreter.h"

Interpreter::Interpreter(Parser parser) : parser(parser) {}; 

int Interpreter::visit(AST_node* node) {
  if (!node) {
    std::cout << "Syntax error\n";
    exit(1);
  }
  if (node->isUnary) {
    if (node->token.type == Type::PLUS) {
      return visit(node->left);
    } else if (node->token.type == Type::MINUS) {
      return -1 * visit(node->left);
    }
  }

  if (node->token.type == Type::PLUS) 
    return visit(node->left) + visit(node->right);
  else if (node->token.type == Type::MINUS)
    return visit(node->left) - visit(node->right);
  else if (node->token.type == Type::MUL)
    return visit(node->left) * visit(node->right);
  else if (node->token.type == Type::DIV)
    return visit(node->left) / visit(node->right);
  else if (node->left == nullptr && node->right == nullptr &&
           node->token.type == Type::INTEGER)
    return *(node->token.value);

  return 0;
}


int Interpreter::interpret() {
  AST_node* root = parser.parse();
  //print_AST(root);
  return visit(root);
}

void Interpreter::print_AST(AST_node* root) {
  if (root == nullptr) return;
  print_AST(root->left);
  std::cout << root->token << '\n';
  print_AST(root->right);
}
