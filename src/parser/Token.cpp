#include "Token.h"
#include <iostream>
using namespace parser;

Token::Token()
    : type(Type::None) {}

Token::Token(Type t_)
    : type(t_) {}

Token::Token(int i_)
    : type(Type::Int), intValue(i_) {}

Token::Token(Type t_, std::string s_)
    : type(t_)
{
    if(t_ != Type::Ident && t_ != Type::String)
        throwTypeError("cannot set text to non-string");
    else
        stringValue = s_;
}

int Token::getNumber(){
    if(type != Type::Int)
        throwTypeError("type is not integer");
    return intValue;
}

std::string Token::getString() {
    if(type != Type::Ident && type != Type::String)
        throwTypeError("type is not string");
    return stringValue;
}

const std::string Token::atomNames[(int)Type::TYPE_COUNT] = {
       "Ident", "Int", "String",

       "Print", "Program", "SharedLib", "Lib",
       "def", "end", "fun",

       "if", "else", "while",

       "or", "and",

       "'", "(", ")", "[", "]",
       ",", ":", ";",
       "==", "=", "+", "+=", "!=",

       "newline", "eof", "none"
};

std::string Token::toString(Token::Type type)
{
    return atomNames[(int)type];
}

// check if given string is a known atom
Token::Type Token::findToken(std::string token) {
    for(int i=(int)Type::Print; i<=(int)Type::And; i++){
        if(token == atomNames[i])
            return static_cast<Type>(i);
    }
    return Type::None;
}

void Token::throwTypeError(std::string msg)
{
    throw std::runtime_error("Token error: " + msg);
}
