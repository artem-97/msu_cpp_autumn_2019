#pragma once

#include <iostream>
#include <string>
#include <optional>

const int MAX_N = 6; // max len of input int

enum class Type {
	INTEGER,
	PLUS,
	MINUS,
	MUL,
	DIV,
	LP,	// left paranthesis
	RP,	// right paranthesis
	END,
  ERR,
};

struct Token {
  Type type;
  std::optional<int> value = std::nullopt;

  Token(Type, std::optional<int>);
  Token(Type);
  friend std::ostream& operator << (std::ostream& stream, const Token& token);
};