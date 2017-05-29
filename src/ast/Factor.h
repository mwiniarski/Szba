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
    ~Factor(){}

    void add(std::unique_ptr<Constant> c_) {
        if(!isList)
            throw std::runtime_error("Factor error: adding value to non-list");
        constants.push_back(std::move(c_));
    }

    std::string toString() const override {
        std::string ret;
        for(auto i = constants.begin(); i != constants.end(); ++i) {
            ret += (*i)->toString();
        }
        return ret;
    }
};

}
#endif
