#ifndef PARSER_H_
#define PARSER_H_

#include "Scanner.h"
#include <ast/ast.h>
using namespace ast;

namespace parser {

class Parser {
public:
    Parser(std::unique_ptr<Scanner> scanner_);
    ~Parser();
    std::unique_ptr<Program> parse();
private:
    std::unique_ptr<Program> program();
    std::unique_ptr<Block> block();
    std::unique_ptr<Statement> statement();
    std::unique_ptr<WhileStat> whileStat();
    std::unique_ptr<VarFactor> varFactor();
    std::unique_ptr<PrintStat> printStat();
    std::unique_ptr<ExecStat> execStat();
    std::unique_ptr<FuncInvoke> funcInvoke();
    std::unique_ptr<FuncDef> funcDef();
    std::unique_ptr<IfStat> ifStat();
    std::unique_ptr<LogicCond> logicCond();
    std::unique_ptr<Block> elseStat();
    std::unique_ptr<Assignment> assignment();
    std::unique_ptr<Expression> expression();
    std::unique_ptr<Dictionary> dictionary();
    std::unique_ptr<Operation> operation();
    std::unique_ptr<Factor> factor();
    std::unique_ptr<Constant> constant();
    std::unique_ptr<Var> var();

    std::string exec();
    RelOp relOp();
    AssignOp assignOp();
    Token requireToken(Token::Type exp);
    bool checkToken(Token::Type exp);

    void advance();

    void throwUnexpectedInput(Token::Type expected);

    std::unique_ptr<Scanner> scanner;
};

}
#endif //PARSER_H_
