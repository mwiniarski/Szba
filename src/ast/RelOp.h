#ifndef RELOP_H_
#define RELOP_H_

#include <string>
namespace ast {

enum class RelOp {
    EqEq, NotEq
};

std::string toString(RelOp o);
}
#endif
