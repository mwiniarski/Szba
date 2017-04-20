#ifndef TKOM_PARSER_SCANNER_H_
#define TKOM_PARSER_SCANNER_H_

#include <istream>

#include "Token.h"

namespace parser
{

class Scanner
{
public:
    Scanner(std::istream& in);

    Scanner(const Scanner&) = delete;
    const Scanner& operator=(const Scanner&) = delete;

    void readNextToken();
    Token getToken() const;

private:
    void ignoreWhitespaces();
    // caly kod zrodlowy
    std::istream& in;

    // ostatnio odczytany token
    Token token;
};

} // namespace parser

#endif // TKOM_PARSER_SCANNER_H_
