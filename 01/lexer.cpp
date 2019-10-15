#include "lexer.h"

Lexer::Lexer() {
    std::getline(std::cin, text);
}
		
void Lexer::err() const {
	std::cout << "Invalid char\n";
}

Token Lexer::get_next_token() {
  if (text[pos] == '\n' || text[pos] == 'q') return Token(Type::END);
  
  while (pos < text.length() && std::isspace(text[pos])) {
    pos++;
  }

  if (pos >= text.length()) {
    return Token(Type::END);
	}


	char curr = text[pos]; 
  if (curr == '+') {
    ++pos;
    return Token(Type::PLUS);
  }
  if (curr == '-') {
    pos++;
    return Token(Type::MINUS);
  }
  if (curr == '*') {
    pos++;
    return Token(Type::MUL);
  }
  if (curr == '/') {
    pos++;
    return Token(Type::DIV);
  }
  if (curr == '(') {
    pos++;
    return Token(Type::LP);
  }
  if (curr == ')') {
    pos++;
    return Token(Type::RP);
  }
  if (std::isdigit(curr)) {
    char buff[MAX_N];
    int i = 0;

  while (pos < text.length() && std::isdigit(text[pos])){
    buff[i] = text[pos];
    ++i;
     ++pos;
    }

  return Token(Type::INTEGER, std::stoi(std::string(buff, MAX_N)));
	}

  err();
  return Token(Type::ERR);
	}

int Lexer::expr() {
  Token curr = this->get_next_token();
  int res = 0;
  while (curr.type != Type::END && curr.type != Type::ERR) {
    curr = this->get_next_token();
  }
  return res;
  }

