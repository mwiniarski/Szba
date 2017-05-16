#ifndef BLOCK_H_
#define BLOCK_H_

#include <vector>
#include "Statement.h"

namespace ast {

class Block {
public:
    Block();

    void add(std::unique_ptr<Statement> s_) {
        statements.push_back(std::move(s_));
    }
private:
    std::vector<std::unique_ptr<Statement>> statements;
};

}
#endif