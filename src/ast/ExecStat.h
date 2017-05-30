#ifndef EXECSTAT_H_
#define EXECSTAT_H_

#include "Expression.h"
#include "Statement.h"
#include <array>

namespace ast {

class ExecStat : public Statement {
public:
    ExecStat(std::string ex_,
             std::unique_ptr<Expression> e1_,
             std::unique_ptr<Expression> e2_,
             std::unique_ptr<Expression> e3_)
                :exec(ex_)
             {
                 exprs[0] = std::move(e1_);
                 exprs[1] = std::move(e2_);
                 exprs[2] = std::move(e3_);
             }
    ~ExecStat() {}

    std::string toString() const override {
        std::string ret = exec;
        for(int i=0;i<3;i++){
            ret += exprs[i]->toString();
        }
        return ret;
    }
private:
    std::string exec;
    std::array<std::unique_ptr<Expression>, 3> exprs;
};

}
#endif
