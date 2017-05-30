#ifndef CONSTANT_H_
#define CONSTANT_H_

#include "LogicExpr.h"
namespace ast {

class Constant {
public:
    Constant(std::string str_)
        :str(str_), isstring(true)
    {}

    Constant(int iint_)
        :iint(iint_), isstring(false)
    {}
    ~Constant() {}

    bool isString() {return isstring;}
    int getInt(){ return iint;}
    std::string getString() { return str;}

    std::string toString() const { return isstring ? str : std::to_string(iint);}
private:
    std::string str;
    int iint;
    bool isstring;
};


}
#endif
