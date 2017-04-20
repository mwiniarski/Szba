#ifndef TKOM_PARSER_TOKEN_H_
#define TKOM_PARSER_TOKEN_H_

#include <ostream>
#include <string>

namespace parser
{
    
static std::string atomName[] = {
    "Ident", "Int", "String",

    "Print", "Program", "SharedLib", "Lib",
    "Def", "End",

    "If", "Elseif", "Else", "While",

    "True", "False", "Or", "And",

    "Quot", "Lbra", "Rbra", "Lsquare", "Rsquare",
    "Comma", "Colon", "Semic", "Dot",
    "Eq", "Plus", "Pluseq", "Noteq",

    "Eof"
};

class Token
{
public:
    enum class Type
    {
        //constants
        Ident, Int, String,

        //key functions
        Print, Program, SharedLib, Lib,
        Def, End,

        //if & loop
        If, Elseif, Else, While,

        //logic
        True, False, Or, And,

        //op
        Quot, Lbra, Rbra, Lsquare, Rsquare,
        Comma, Colon, Semic, Dot,
        Eq, Plus, Pluseq, Noteq,

        Eof
    };

    Token();
    Token(Type t);
    Token(Type t, int i);
    Token(Type t, std::string s);

    Type getType() const { return type; }
    std::string getString() { return stringValue; }
    int getNumber() { return intValue; }
    static std::string toString(Token::Type type);

private:
    Type type;

    // jesli wczytany typ to ident, string lub liczba należy przechować wartość
    int intValue;
    std::string stringValue;
};

inline std::ostream& operator<<(std::ostream& o, Token::Type type)
{
    return o << Token::toString(type);
}

} // namespace parser

#endif // TKOM_PARSER_TOKEN_H_
