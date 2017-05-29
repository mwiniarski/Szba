#ifndef ASSIGNMENT_H_
#define ASSIGNMENT_H_

#include "Statement.h"
#include "AssignExpr.h"
#include "Operator.h"

namespace ast {

class Assignment : public Statement {
public:
    Assignment(std::unique_ptr<AssignExpr> a_,
               Operator o_,
               std::unique_ptr<Expression> e_)
               :assignExpr(std::move(a_)), oper(o_), expr(std::move(e_))
               {}
    ~Assignment() {}

    std::string toString() const override {
        return assignExpr->toString() + ast::toString(oper) + expr->toString();
    }
private:
    std::unique_ptr<AssignExpr> assignExpr;
    Operator oper;
    std::unique_ptr<Expression> expr;
};

}
#endif
