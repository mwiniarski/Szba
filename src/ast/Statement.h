#ifndef STATEMENT_H_
#define STATEMENT_H_

#include <vector>
#include <string>
namespace ast {

class Statement {
public:
    virtual ~Statement() {}

    virtual std::string toString() const = 0;
};

}
#endif
