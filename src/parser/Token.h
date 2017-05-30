#ifndef TKOM_PARSER_TOKEN_H_
#define TKOM_PARSER_TOKEN_H_

#include <ostream>
#include <string>

namespace parser
{

class Token
{
public:
    enum class Type
    {
        //constants
        Ident, Int, String,

        //key functions
        Print, Program, SharedLib, Lib,
        Def, End, Fun,

        //if & loop
        If, Else, While,

        //logic
        Or, And,

        //op
        Quot, Lbra, Rbra, Lsquare, Rsquare,
        Comma, Colon, Semic,
        Eqeq, Eq, Plus, Pluseq, Noteq,

        Newline, Eof, None, TYPE_COUNT
    };

    Token();
    Token(Type t);
    Token(int i);
    Token(Type t, std::string s);

    Type getType() const { return type; }
    int getNumber();
    std::string getString();

    static Type findToken(std::string token);
    static std::string toString(Token::Type type);

private:
    static const std::string atomNames[(int)Type::TYPE_COUNT];
    void throwTypeError(std::string msg);
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
