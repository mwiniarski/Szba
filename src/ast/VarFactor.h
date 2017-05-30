#ifndef VARFACTOR_H_
#define VARFACTOR_H_

namespace ast {

class VarFactor {
public:
    virtual ~VarFactor() {}

    virtual std::string toString() const = 0;
};

}
#endif
