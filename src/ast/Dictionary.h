#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include "Factor.h"
namespace ast {

class Dictionary : public Expression {
public:
    typedef std::pair<std::string, std::unique_ptr<Factor>> pair;

private:
    std::vector<pair> elements;

public:
    void add(pair elem_) {
        elements.push_back(std::move(elem_));
    }
    ~Dictionary() {}
};

}
#endif
