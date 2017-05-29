#ifndef EXPRESSION_H_
#define EXPRESSION_H_

#include <memory>
#include <string>
#include <vector>

namespace ast {

class Expression {
public:
    virtual ~Expression() {}

    virtual std::string toString() const = 0;
};

}
#endif
