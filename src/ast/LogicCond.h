#ifndef LOGICCOND_H_
#define LOGICCOND_H_

#include "LogicExpr.h"
#include "RelOp.h"

namespace ast {

class LogicCond : public Statement {
public:
    LogicCond(std::unique_ptr<LogicExpr> le1_,
              RelOp ro_,
              std::unique_ptr<LogicExpr> le2_)
              :expr1(std::move(le1_)), oper(ro_), expr2(std::move(le2_))
              {}
    ~LogicCond() {}

    std::string toString() const override {
        return expr1->toString() + ast::toString(oper) + expr2->toString();
    }
private:
    std::unique_ptr<LogicExpr> expr1;
    RelOp oper;
    std::unique_ptr<LogicExpr> expr2;
};

}
#endif
