#include <iostream>

#include "ast.h"
#include "interpreter.h"
#include "lexer.h"
#include "parser.h"
#include "token.h"

void calc() {
  std::cout << "calc> ";
  while (true) {
    Lexer lexer;
    Parser parser(lexer);
    Interpreter interpreter(parser);
    std::cout << "calc> ";
    std::cout << interpreter.interpret();
    std::cout << '\n';
    std::cout << "\ncalc> ";
  }
}

void calc_pipe() {
  Lexer lexer;
  Parser parser(lexer);
  Interpreter interpreter(parser);
  std::cout << interpreter.interpret();
}

int main() {
  calc_pipe();
  return 0;
}
