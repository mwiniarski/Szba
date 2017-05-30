#ifndef WHILESTAT_H_
#define WHILESTAT_H_

#include "Block.h"
#include "LogicCond.h"

namespace ast {

class WhileStat : public Statement {
public:
    WhileStat(std::unique_ptr<LogicCond> lc_,
           std::unique_ptr<Block> b_)
           :logicCond(std::move(lc_)), mainBlock(std::move(b_))
           {}
    ~WhileStat() {}

    std::string toString() const override {
        return logicCond->toString() + mainBlock->toString();
    }
private:
    std::unique_ptr<LogicCond> logicCond;
    std::unique_ptr<Block> mainBlock;
};

}
#endif
