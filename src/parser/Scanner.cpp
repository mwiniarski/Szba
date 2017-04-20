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
