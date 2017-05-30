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
    auto prog = std::make_unique<Program>();
    while(checkToken(Token::Type::Def))
        prog->addFuncDef(funcDef());

    prog->addBlock(block());
    requireToken(Token::Type::Eof);
    return prog;
}

std::unique_ptr<Block> Parser::block()
{
    auto tBlock = std::make_unique<Block>();
    while(checkToken(Token::Type::Ident) ||
          checkToken(Token::Type::If) ||
          checkToken(Token::Type::While) ||
          checkToken(Token::Type::Fun) ||
          checkToken(Token::Type::Print) ||
          checkToken(Token::Type::Program) ||
          checkToken(Token::Type::SharedLib) ||
          checkToken(Token::Type::Lib))
    {
        tBlock->add(statement());
        requireToken(Token::Type::Newline);
    }
    return tBlock;
}

std::unique_ptr<Statement> Parser::statement()
{
    std::unique_ptr<Statement> stat;
    if(checkToken(Token::Type::Ident))
        stat = std::move(assignment());
    else
    if(checkToken(Token::Type::If))
        stat = std::move(ifStat());
    else
    if(checkToken(Token::Type::While))
        stat = std::move(whileStat());
    else
    if(checkToken(Token::Type::Fun))
        stat = std::move(funcInvoke());
    else
    if(checkToken(Token::Type::Print))
        stat = std::move(printStat());
    else
        //exec
        stat = std::move(execStat());

    return stat;
}

std::unique_ptr<WhileStat> Parser::whileStat()
{
    requireToken(Token::Type::While);
    auto logiccond = logicCond();
    requireToken(Token::Type::Colon);
    requireToken(Token::Type::Newline);
    auto bl = block();
    requireToken(Token::Type::End);
    return std::make_unique<WhileStat>(std::move(logiccond), std::move(bl));
}

std::unique_ptr<PrintStat> Parser::printStat()
{
    requireToken(Token::Type::Print);
    requireToken(Token::Type::Lbra);
    auto con = varFactor();
    requireToken(Token::Type::Rbra);
    return std::make_unique<PrintStat>(std::move(con));
}

std::unique_ptr<ExecStat> Parser::execStat()
{
    std::string ex = exec();
    requireToken(Token::Type::Lbra);
    auto expr1 = expression();
    requireToken(Token::Type::Comma);
    auto expr2 = expression();
    requireToken(Token::Type::Comma);
    auto expr3 = expression();
    requireToken(Token::Type::Rbra);
    return std::make_unique<ExecStat>(ex,
                                      std::move(expr1),
                                      std::move(expr2),
                                      std::move(expr3));
}

std::unique_ptr<FuncDef> Parser::funcDef()
{
    requireToken(Token::Type::Def);
    auto ret = std::make_unique<FuncDef>(var());
    requireToken(Token::Type::Lbra);
    if(!checkToken(Token::Type::Rbra)) {
        ret->addArg(var());
        while(checkToken(Token::Type::Comma)) {
            advance();
            ret->addArg(var());
        }
        requireToken(Token::Type::Rbra);
    } else
        advance();

    requireToken(Token::Type::Colon);
    requireToken(Token::Type::Newline);
    ret->addBlock(block());
    requireToken(Token::Type::End);
    requireToken(Token::Type::Newline);
    return ret;
}

std::unique_ptr<FuncInvoke> Parser::funcInvoke()
{
    requireToken(Token::Type::Fun);
    auto ret = std::make_unique<FuncInvoke>(var());
    requireToken(Token::Type::Lbra);

    if(!checkToken(Token::Type::Rbra)) {
        ret->addArg(expression());
        while(checkToken(Token::Type::Comma)) {
            advance();
            ret->addArg(expression());
        }
        requireToken(Token::Type::Rbra);
    } else
        advance();

    return ret;
}

std::unique_ptr<IfStat> Parser::ifStat()
{
    requireToken(Token::Type::If);
    auto logiccond = logicCond();
    requireToken(Token::Type::Colon);
    requireToken(Token::Type::Newline);
    auto bl = block();

    auto ifstat = std::make_unique<IfStat>(std::move(logiccond), std::move(bl));

    if(checkToken(Token::Type::End)) {
        advance();
    } else {
        ifstat->addElse(elseStat());
    }

    return ifstat;
}

std::unique_ptr<LogicCond> Parser::logicCond()
{
    auto e1 = operation();
    RelOp ro = relOp();
    auto e2 = operation();
    return std::make_unique<LogicCond>(std::move(e1), ro, std::move(e2));
}

std::unique_ptr<VarFactor> Parser::varFactor()
{
    if(checkToken(Token::Type::Int) ||
       checkToken(Token::Type::String) ||
       checkToken(Token::Type::Lsquare))
       return factor();

    return var();
}

std::unique_ptr<Block> Parser::elseStat()
{
    requireToken(Token::Type::Else);
    requireToken(Token::Type::Newline);
    return block();
}

std::unique_ptr<Assignment> Parser::assignment()
{
    auto v = var();
    AssignOp op = assignOp();
    auto expr = expression();
    return std::make_unique<Assignment>(std::move(v), op, std::move(expr));
}

std::unique_ptr<Expression> Parser::expression()
{
    if(checkToken(Token::Type::Int) ||
       checkToken(Token::Type::String)  ||
       checkToken(Token::Type::Lsquare) ||
       checkToken(Token::Type::Ident))
        return operation();

    return dictionary();
}

std::unique_ptr<Dictionary> Parser::dictionary()
{
    requireToken(Token::Type::Lbra);
    auto dict = std::make_unique<Dictionary>();
    auto val = var();
    requireToken(Token::Type::Colon);
    dict->add(std::make_pair(std::move(val), factor()));

    while(checkToken(Token::Type::Comma))
    {
        advance();
        val = var();
        requireToken(Token::Type::Colon);
        dict->add(std::make_pair(std::move(val), factor()));
    }

    requireToken(Token::Type::Rbra);
    return dict;
}

std::unique_ptr<Operation> Parser::operation()
{
    auto oper = std::make_unique<Operation>(varFactor());

    while(checkToken(Token::Type::Plus)) {
        advance();
        oper->add(varFactor());
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
    auto tFactor = std::make_unique<Factor>();
    tFactor->add(constant());

    while(checkToken(Token::Type::Comma)) {
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
        return std::make_unique<Constant>(val);
    }
}

std::unique_ptr<Var> Parser::var()
{
    auto ret = std::make_unique<Var>(requireToken(Token::Type::Ident).getString());
    return ret;
}
std::string Parser::exec()
{
    std::string ex;
    if(checkToken(Token::Type::Program)){
        ex = "prog";
        advance();
    }
    else
    if(checkToken(Token::Type::SharedLib)){
        ex = "shared";
        advance();
    }
    else {
        requireToken(Token::Type::Lib);
        ex = "lib";
    }
    return ex;
}

RelOp Parser::relOp()
{
    if(checkToken(Token::Type::Eqeq)){
        advance();
        return RelOp::EqEq;
    }

    requireToken(Token::Type::Noteq);
    return RelOp::NotEq;
}

AssignOp Parser::assignOp()
{
    if(checkToken(Token::Type::Eq)){
        advance();
        return AssignOp::Eq;
    }

    requireToken(Token::Type::Pluseq);
    return AssignOp::PlusEq;
}

Token Parser::requireToken(Token::Type expected)
{
    const auto token = scanner->getToken();
    const auto type = token.getType();
    if (type != expected)
        throwUnexpectedInput(expected);
    advance();
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
                                                     + ", expecting: " + Token::toString(expected)
                                                     + " on line " + std::to_string(scanner->getCurrentLine()));
}
