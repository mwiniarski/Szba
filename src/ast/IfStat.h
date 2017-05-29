#ifndef IFSTAT_H_
#define IFSTAT_H_

#include "Block.h"
#include "LogicCond.h"

namespace ast {

class IfStat : public Statement {
public:
    IfStat(std::unique_ptr<LogicCond> lc_,
           std::unique_ptr<Block> b_)
           :logicCond(std::move(lc_)), mainBlock(std::move(b_))
           {}
    ~IfStat() {}

    void addElse(std::unique_ptr<Block> eb_) {
        elseBlock = std::move(eb_);
    }

    std::string toString() const override {
        return logicCond->toString() + mainBlock->toString() + (elseBlock ? elseBlock->toString() : "");
    }
private:
    std::unique_ptr<LogicCond> logicCond;
    std::unique_ptr<Block> mainBlock;
    std::unique_ptr<Block> elseBlock;
};

}
#endif
