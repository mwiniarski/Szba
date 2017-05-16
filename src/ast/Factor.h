#ifndef FACTOR_H_
#define FACTOR_H_

#include "Expression.h"
#include "Constant.h"

namespace ast {

class Factor : public Expression {
private:
    std::vector<std::unique_ptr<Constant>> constants;
    bool isList;

public:
    Factor()
        :isList(true)
    {}
    Factor(std::unique_ptr<Constant> c_)
        :isList(false)
    {
        constants.push_back(std::move(c_));
    }

    void add(std::unique_ptr<Constant> c_) {
        constants.push_back(std::move(c_));
    }
};

}
#endif
