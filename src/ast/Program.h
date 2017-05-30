#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "Block.h"

namespace ast {

class Program {
public:
    Program()
    {}

    void addBlock(std::unique_ptr<Block> bl_) {
        block = std::move(bl_);
    }

    void addFuncDef(std::unique_ptr<FuncDef> fd_){
        functions.push_back(std::move(fd_));
    }

    std::string toString() {
        std::string ret;
        for(auto i = functions.begin(); i != functions.end(); ++i){
            ret += (*i)->toString();
        }
        ret += block->toString();
        return ret;
    }

private:
    std::unique_ptr<Block> block;
    std::vector<std::unique_ptr<FuncDef>> functions;
};

}
#endif
