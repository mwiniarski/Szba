#ifndef OPERATION_H_
#define OPERATION_H_

#include "VarFactor.h"

namespace ast {

class Operation : public Expression {
private:
    std::vector<std::unique_ptr<VarFactor>> varfactors;
public:
    Operation(std::unique_ptr<VarFactor> c_)
    {
        varfactors.push_back(std::move(c_));
    }
    ~Operation(){}

    void add(std::unique_ptr<VarFactor> c_) {
        varfactors.push_back(std::move(c_));
    }

    std::string toString() const override {
        auto i = varfactors.begin();
        std::string ret = (*i++)->toString();
        for(; i != varfactors.end(); ++i) {
            ret += (*i)->toString();
        }
        return ret;
    }
};

}
#endif
