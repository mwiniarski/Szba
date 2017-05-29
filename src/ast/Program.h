#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "Block.h"

namespace ast {

class Program {
private:
    std::unique_ptr<Block> block;

public:
    Program(std::unique_ptr<Block> b_)
        :block(std::move(b_))
    {}

    std::string toString() { return block->toString();}
};

}
#endif
