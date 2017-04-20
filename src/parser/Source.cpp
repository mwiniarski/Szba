#include "Source.h"

using namespace parser;

Source::Source(std::istream& in_)
    : stream(in_)
{
    nextLine();
}

bool Source::nextLine(){
    if(stream.eof())
        return false;

    getline(stream, currentLine);
    currentLine.push_back('\n');
    it = currentLine.begin();
    return true;
}

int Source::nextChar(){
    if(it == currentLine.end())
        if(!nextLine())
            return EOF;

    return *it++;
}
