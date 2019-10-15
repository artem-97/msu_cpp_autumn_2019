#include "token.h"

Token::Token(Type type, std::optional<int> value) : 
  type (type), value (value) {};

Token::Token(Type type) : type (type) {};

std::ostream& operator << (std::ostream& os, const Token& token) {
  std::string type;
  switch (token.type) {
    case Type::INTEGER : 
      type = "INTEGER";
      break;
    case Type::PLUS :
      type = "PLUS";
      break;
    case Type::MINUS :
      type = "MINUS";
      break;
    case Type::MUL :
      type = "MUL";
      break;
    case Type::DIV :
      type = "DIV";
      break;
    case Type::LP :
      type = "LP";
      break;
    case Type::RP :
      type = "RP";
      break;
    case Type::END :
      type = "END";
      break;
    case Type::ERR :
      type = "ERR";
      break;
    default:
      type = "ERR";
      break;
  }

  if (token.value) {
    std::cout << "Token(" << type << ", " << *token.value << ")";
  } else {
    std::cout << "Token(" << type << ")";
  }
  return os;
} 