#ifndef LOGICEXPR_H_
#define LOGICEXPR_H_

namespace ast {

class LogicExpr {
public:
    virtual ~LogicExpr() {}

    virtual std::string toString() const = 0;
};

}
#endif
