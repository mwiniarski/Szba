#ifndef ASSIGNMENT_H_
#define ASSIGNMENT_H_

#include "Statement.h"
#include "Var.h"
#include "AssignOp.h"

namespace ast {

class Assignment : public Statement {
public:
    Assignment(std::unique_ptr<Var> a_,
               AssignOp o_,
               std::unique_ptr<Expression> e_)
               :var(std::move(a_)), oper(o_), expr(std::move(e_))
               {}
    ~Assignment() {}

    std::string toString() const override {
        return var->toString() + ast::toString(oper) + expr->toString();
    }
private:
    std::unique_ptr<Var> var;
    AssignOp oper;
    std::unique_ptr<Expression> expr;
};

}
#endif
