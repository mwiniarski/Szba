#ifndef SOURCE_H_
#define SOURCE_H_

#include <istream>

namespace parser {

class Source {
public:
    Source(std::istream& in);

    Source(const Source&) = delete;
    const Source& operator=(const Source&) = delete;

    int nextChar();
    int getLineNumber() {return currentLineNumber;}
private:
    int currentLineNumber;
    bool nextLine();
    std::string::iterator it;
    std::string currentLine;
    std::istream& stream;
};

} // namespace

#endif // SOURCE_H_
