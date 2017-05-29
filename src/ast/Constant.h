#ifndef CONSTANT_H_
#define CONSTANT_H_

namespace ast {

class Constant {
public:
    Constant(std::string str_)
        :str(str_), isstring(true)
    {}

    Constant(int iint_)
        :iint(iint_), isstring(false)
    {}

    bool isString() {return isstring;}
    int getInt(){ return iint;}
    std::string getString() { return str;}

    std::string toString() { return isString() ? str : std::to_string(iint);}
private:
    std::string str;
    int iint;
    bool isstring;
};


}
#endif
