#include "Token.h"

using namespace parser;

Token::Token()
    : type(Type::Eof) {}

Token::Token(Type t_)
    : type(t_) {}

Token::Token(Type t_, int i_)
    : type(t_), intValue(i_) {}

Token::Token(Type t_, std::string s_)
    : type(t_), stringValue(s_) {}

std::string Token::toString(Token::Type type)
{
    return atomName[(int)type];
}
