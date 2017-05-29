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
    auto assign = assignment();
    requireToken(Token::Type::Newline);
    advance();
    return assign;
}

std::unique_ptr<Assignment> Parser::assignment()
{
    auto v = var();
    Operator op = oper();
    auto expr = expression();
    return std::make_unique<Assignment>(std::move(v), op, std::move(expr));
}

std::unique_ptr<Expression> Parser::expression()
{
    if(checkToken(Token::Type::Int) ||
       checkToken(Token::Type::String)  ||
       checkToken(Token::Type::Lsquare))
        return operation();

    else if(checkToken(Token::Type::Lbra))
        return dictionary();

    else if(checkToken(Token::Type::Ident))
        return var();

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
    auto val = var();
    requireToken(Token::Type::Colon);
    advance();
    dict->add(std::make_pair(std::move(val), factor()));

    while(checkToken(Token::Type::Comma))
    {
        advance();
        val = var();
        requireToken(Token::Type::Colon);
        advance();
        dict->add(std::make_pair(std::move(val), factor()));
    }

    requireToken(Token::Type::Rbra);
    advance();
    return dict;
}

std::unique_ptr<Operation> Parser::operation()
{
    auto oper = std::make_unique<Operation>(factor());

    while(checkToken(Token::Type::Plus)) {
        advance();
        oper->add(factor());
    };

    return oper;
}

std::unique_ptr<Factor> Parser::factor()
{
    if(checkToken(Token::Type::Int) ||
       checkToken(Token::Type::String))
        return std::make_unique<Factor>(constant());

    //factor is list
    requireToken(Token::Type::Lsquare);
    advance();
    auto tFactor = std::make_unique<Factor>();
    tFactor->add(constant());

    while(checkToken(Token::Type::Comma)) {
        advance();
        tFactor->add(constant());
    };

    requireToken(Token::Type::Rsquare);
    advance();
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

std::unique_ptr<Var> Parser::var()
{
    auto ret = std::make_unique<Var>(requireToken(Token::Type::Ident).getString());
    advance();
    return ret;
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
