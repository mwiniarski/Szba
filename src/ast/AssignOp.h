#ifndef ASSIGNOP_H_
#define ASSIGNOP_H_

#include <string>
namespace ast {

enum class AssignOp {
    Eq, PlusEq
};

std::string toString(AssignOp o);
}
#endif
