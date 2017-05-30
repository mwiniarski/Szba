#ifndef PRINTSTAT_H_
#define PRINTSTAT_H_

#include "VarFactor.h"
#include "Statement.h"

namespace ast {

class PrintStat : public Statement {
private:
    std::unique_ptr<VarFactor> print;
public:
    PrintStat(std::unique_ptr<VarFactor> p_)
        :print(std::move(p_))
    {}

    ~PrintStat(){}

    std::string toString() const override {
        return print->toString();
    }
};

}
#endif
