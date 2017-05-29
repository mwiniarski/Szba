#ifndef OPERATOR_H_
#define OPERATOR_H_

#include <string>
namespace ast {

enum class Operator {
    Eq, PlusEq
};

std::string toString(Operator o);
inline std::ostream& operator<<(std::ostream& out, Operator o) { return out << toString(o); }

}
#endif
