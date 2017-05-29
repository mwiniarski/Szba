#ifndef OPERATION_H_
#define OPERATION_H_

#include "Factor.h"

namespace ast {

class Operation : public Expression {
private:
    std::vector<std::unique_ptr<Factor>> factors;
public:
    Operation(std::unique_ptr<Factor> c_)
    {
        factors.push_back(std::move(c_));
    }
    ~Operation(){}

    void add(std::unique_ptr<Factor> c_) {
        factors.push_back(std::move(c_));
    }

    std::string toString() const override {
        auto i = factors.begin();
        std::string ret = (*i++)->toString();
        for(; i != factors.end(); ++i) {
            ret += (*i)->toString();
        }
        return ret;
    }
};

}
#endif
