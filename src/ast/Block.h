#ifndef BLOCK_H_
#define BLOCK_H_

#include <vector>
#include "Statement.h"

namespace ast {

class Block {
public:
    void add(std::unique_ptr<Statement> s_) {
        statements.push_back(std::move(s_));
    }
    ~Block() {}

    std::string toString() {
        std::string ret;
        for(auto i = statements.begin(); i!= statements.end(); ++i) {
            ret += (*i)->toString();
        }
        return ret;
    }
private:
    std::vector<std::unique_ptr<Statement>> statements;
};

}
#endif
