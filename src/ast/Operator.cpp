#include "Operator.h"

std::string ast::toString(Operator o){
    switch (o){
        case Operator::Eq:  return "=";
        case Operator::PlusEq: return "+=";
    }
    return "unknown operator";
}
