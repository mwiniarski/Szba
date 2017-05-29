#include "AssignOp.h"

std::string ast::toString(AssignOp o){
    switch (o){
        case AssignOp::Eq:  return "=";
        case AssignOp::PlusEq: return "+=";
    }
    return "unknown operator";
}
