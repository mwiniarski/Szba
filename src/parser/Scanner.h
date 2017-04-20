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
    Scanner(std::unique_ptr<Source> src);

    Scanner(const Scanner&) = delete;
    const Scanner& operator=(const Scanner&) = delete;

    void readNextToken();
    Token getToken() const;

private:
    void ignoreWhitespaces();
    void next();

    int currentChar;
    // ostatnio odczytany token
    Token token;
    std::unique_ptr<Source> source;
};

} // namespace parser

#endif // SCANNER_H_
