#include "Scanner.h"

#include <limits>
#include <cctype>
#include <stdexcept>

using namespace parser;

Scanner::Scanner(std::unique_ptr<Source> source_)
    : source(std::move(source_))
{
    next();
}

void Scanner::next()
{
    currentChar = source->nextChar();
}

void Scanner::ignoreWhitespaces(){
    while(currentChar == ' '){
        next();
    }
}

bool Scanner::isEof(){
    return currentChar == EOF;
}

void Scanner::readNextToken(){
    ignoreWhitespaces();

    if(isEof()){
        token = TT::Eof;
        return;
    }

    if(isalpha(currentChar)) {
        std::string buf;
        do {
            buf += currentChar;
            next();
        } while(isalnum(currentChar));

        TT type_ = Token::findToken(buf);
        if(type_ != TT::None) {
            token = type_;
        } else
            token = Token(TT::Ident, buf);
        return;
    }

    if(isdigit(currentChar)){
        std::string buf;

        int i = 0;
        for(; i< 10; i++) {
            buf += currentChar;
            next();
            if(!isdigit(currentChar))
                break;
        }

        if(i == 9) {
            throwScannerError("too large number");
        }

        //TODO: polaczenie int-string
        token = stoi(buf);
        return;
    }

    if(currentChar == '\'') {
        std::string buf;
        next();

        while(currentChar != '\'') {
            if(currentChar == '\n')
                throwScannerError("string breaks line");

            buf += currentChar;
            next();
        }

        token = Token(TT::String, buf);
        return;
    }
    
    switch(currentChar) {
        case '\n': token = TT::Newline; break;
        case '\'': token = TT::Quot; break;
        case '(' : token = TT::Lbra; break;
        case ')' : token = TT::Rbra; break;
        case '[' : token = TT::Lsquare; break;
        case ']' : token = TT::Rsquare; break;
        case ',' : token = TT::Comma; break;
        case '.' : token = TT::Dot; break;
        case ';' : token = TT::Semic; break;
        case ':' : token = TT::Colon; break;
        case '!' : next();  if(currentChar == '=')
                                token = TT::Noteq;
                            else
                                throwScannerError("wrong character: ! ");
                            break;
        case '+' : next();  if(currentChar == '=')
                                token = TT::Pluseq;
                            else
                                token = TT::Plus;
                            break;
        case '=' : next();  if(currentChar == '=')
                                token = TT::Eqeq;
                            else
                                token = TT::Eq;
                            break;
        default: throwScannerError("wrong character: " + currentChar);
    }

    if(token.getType() != TT::Plus && token.getType() != TT::Eq)
        next();
}

void Scanner::throwScannerError(std::string msg){
    throw std::runtime_error("Scanner error: " + msg);
}
