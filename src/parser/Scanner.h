#ifndef SCANNER_H_
#define SCANNER_H_

#include <istream>
#include <memory>

#include "Source.h"
#include "Token.h"

namespace parser
{

class Scanner
{
public:
    typedef Token::Type TT;
    Scanner(std::unique_ptr<Source> src);

    Scanner(const Scanner&) = delete;
    const Scanner& operator=(const Scanner&) = delete;

    void readNextToken();
    Token getToken() { return token; }

private:
    void throwScannerError(std::string msg);
    void ignoreWhitespaces();
    void next();
    bool isEof();

    int currentChar;
    // ostatnio odczytany token
    Token token;
    std::unique_ptr<Source> source;
};

} // namespace parser

#endif // SCANNER_H_
