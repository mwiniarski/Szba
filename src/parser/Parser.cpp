#include "Parser.h"
using namespace parser;

Parser::Parser(std::unique_ptr<Scanner> scanner_)
    : scanner(std::move(scanner_))
{}
Parser::~Parser() {}

std::unique_ptr<Program> Parser::parse()
{
    advance();
    return program();
}

std::unique_ptr<Program> Parser::program()
{
    auto tBlock = block();
    return std::make_unique<Program>(std::move(tBlock));
}

std::unique_ptr<Block> Parser::block()
{
    auto tBlock = std::make_unique<Block>();
    while(checkToken(Token::Type::Ident))
        tBlock->add(std::move(statement()));
    return tBlock;
}

std::unique_ptr<Statement> Parser::statement()
{
    return assignment();
}

std::unique_ptr<Assignment> Parser::assignment()
{
    auto assignexpr = assignExpr();
    Operator op = oper();
    auto expr = expression();
    return std::make_unique<Assignment>(std::move(assignexpr), op, std::move(expr));
}

std::unique_ptr<AssignExpr> Parser::assignExpr()
{
    std::string var1 = var();
    if(checkToken(Token::Type::Dot))
    {
        advance();
        std::string var2 = requireToken(Token::Type::Ident).getString();
        advance();
        return std::make_unique<AssignExpr>(var1, var2);
    }

    return std::make_unique<AssignExpr>(var1);
}

std::unique_ptr<Expression> Parser::expression()
{
    if(checkToken(Token::Type::Int) ||
       checkToken(Token::Type::String)  ||
       checkToken(Token::Type::Lsquare))
        return factor();

    else if(checkToken(Token::Type::Lbra))
        return dictionary();

    else if(checkToken(Token::Type::Ident))
        return assignExpr();

    else {
        throwUnexpectedInput(Token::Type::Int);
        return nullptr;
    }
}

std::unique_ptr<Dictionary> Parser::dictionary()
{
    requireToken(Token::Type::Lbra);
    advance();
    auto dict = std::make_unique<Dictionary>();
    std::string val = var();
    requireToken(Token::Type::Colon);
    advance();
    dict->add(std::make_pair(val, factor()));

    while(checkToken(Token::Type::Semic))
    {
        advance();
        val = var();
        requireToken(Token::Type::Colon);
        advance();
        dict->add(std::make_pair(val, factor()));
    }

    requireToken(Token::Type::Rbra);
    return dict;
}

std::unique_ptr<Factor> Parser::factor()
{
    if(checkToken(Token::Type::Int) ||
       checkToken(Token::Type::String))
        return std::make_unique<Factor>(constant());

    requireToken(Token::Type::Lsquare);
    auto tFactor = std::make_unique<Factor>();
    tFactor->add(constant());

    while(checkToken(Token::Type::Semic)) {
        advance();
        tFactor->add(constant());
    };

    requireToken(Token::Type::Rsquare);

    return tFactor;
}

std::unique_ptr<Constant> Parser::constant()
{
    if(checkToken(Token::Type::Int)) {
        int val = scanner->getToken().getNumber();
        advance();
        return std::make_unique<Constant>(val);
    } else {
        std::string val = requireToken(Token::Type::String).getString();
        advance();
        return std::make_unique<Constant>(val);
    }
}

Operator Parser::oper()
{
    if(checkToken(Token::Type::Eq)){
        advance();
        return Operator::Eq;
    }

    requireToken(Token::Type::Pluseq);
    advance();
    return Operator::PlusEq;
}

std::string Parser::var()
{
    const auto ret = requireToken(Token::Type::Ident).getString();
    advance();
    return ret;
}

Token Parser::requireToken(Token::Type expected)
{
    const auto token = scanner->getToken();
    const auto type = token.getType();
    if (type != expected)
        throwUnexpectedInput(expected);
    return token;
}

bool Parser::checkToken(Token::Type expected)
{
    return scanner->getToken().getType() == expected;
}

void Parser::advance()
{
    scanner->readNextToken();
}

void Parser::throwUnexpectedInput(Token::Type expected)
{
    throw std::runtime_error("Unexpected token: " + Token::toString(scanner->getToken().getType())
                                                     + ", expecting: " + Token::toString(expected));
}
