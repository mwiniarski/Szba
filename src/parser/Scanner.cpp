#include "Scanner.h"

#include <cctype>
#include <stdexcept>

using namespace parser;

Scanner::Scanner(std::unique_ptr<Source> source_)
    : source(std::move(source_))
{}

Token Scanner::getToken() const
{
    return token;
}

void Scanner::next()
{
    currentChar = source->nextChar();
}
// void Scanner::ignoreWhitespaces(){
//     while (in && std::isspace(in.peek()))
//         in.get();
// }
//
// void Scanner::readNextToken(){
//     ignoreWhitespaces();
//
//     // koniec pliku
//     if(in.eof()) {
//         token = Token();
//         return;
//     }
//
//
// }
