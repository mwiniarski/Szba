#ifndef ASSIGNEXPR_H_
#define ASSIGNEXPR_H_

#include "Expression.h"

namespace ast {

class AssignExpr : public Expression {
public:
    AssignExpr(std::string s_)
        :str1(s_), hasDot(false)
        {}
    AssignExpr(std::string s1_, std::string s2_)
        :str1(s1_), str2(s2_), hasDot(true)
        {}
    AssignExpr() {}

    std::string toString() const override {
        return str1 + (hasDot ? str2 : "");
    }
private:
    std::string str1;
    std::string str2;
    bool hasDot;
};

}
#endif
