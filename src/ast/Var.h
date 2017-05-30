#ifndef VAR_H_
#define VAR_H_

#include "Expression.h"
#include "VarFactor.h"

namespace ast {

class Var : public Expression, public VarFactor {
public:
    Var(std::string str_)
        :str(str_)
    {}
    ~Var() {}

    std::string toString() const { return str; }
private:
    std::string str;
};

}
#endif
