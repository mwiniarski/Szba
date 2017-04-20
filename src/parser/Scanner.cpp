#include "Scanner.h"

#include <cctype>
#include <stdexcept>

using namespace parser;

Scanner::Scanner(std::istream& in_)
    : in(in_)
{}

Token Scanner::getToken() const
{
    return token;
}

void Scanner::ignoreWhitespaces(){
    while (in && std::isspace(in.peek()))
        in.get();
}

void Scanner::readNextToken(){
    ignoreWhitespaces();

    // koniec pliku
    if(in.eof()) {
        token = Token();
        return;
    }


}
