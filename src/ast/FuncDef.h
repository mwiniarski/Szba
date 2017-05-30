#ifndef FUNCDEF_H_
#define FUNCDEF_H_

#include "Block.h"
#include "Var.h"

namespace ast {

class FuncDef {
public:
    FuncDef(std::unique_ptr<Var> v_)
        :funcName(std::move(v_))
    {}
    ~FuncDef() {}

    void addArg(std::unique_ptr<Var> arg_){
        args.push_back(std::move(arg_));
    }

    void addBlock(std::unique_ptr<Block> bl_){
        block = std::move(bl_);
    }

    std::string toString() const {
        std::string ret = funcName->toString();
        for(auto i = args.begin(); i != args.end(); ++i) {
            ret += (*i)->toString();
        }
        ret += block->toString();
        return ret;
    }

private:
    std::unique_ptr<Var> funcName;
    std::vector<std::unique_ptr<Var>> args;
    std::unique_ptr<Block> block;
};

}
#endif
