#include "RelOp.h"

std::string ast::toString(RelOp o){
    switch (o){
        case RelOp::EqEq:  return "==";
        case RelOp::NotEq: return "!=";
    }
    return "unknown operator";
}
