#ifndef FUNCINVOKE_H_
#define FUNCINVOKE_H_

#include "Statement.h"
#include "Var.h"

namespace ast {

class FuncInvoke : public Statement {
public:
    FuncInvoke(std::unique_ptr<Var> name_)
        :funcName(std::move(name_))
    {}
    ~FuncInvoke() {}

    void addArg(std::unique_ptr<Expression> arg_){
        args.push_back(std::move(arg_));
    }

    std::string toString() const override {
        std::string ret = funcName->toString();
        for(auto i = args.begin(); i != args.end(); ++i) {
            ret += (*i)->toString();
        }
        return ret;
    }

private:
    std::unique_ptr<Var> funcName;
    std::vector<std::unique_ptr<Expression>> args;
};

}
#endif
