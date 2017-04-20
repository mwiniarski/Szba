#ifndef SOURCE_H_
#define SOURCE_H_

#include <istream>

namespace parser {

class Source {
public:
    Source(std::istream& in);

    int nextChar();
private:

    bool nextLine();
    std::string::iterator it;
    std::string currentLine;
    std::istream& stream;
};

} // namespace

#endif // SOURCE_H_
