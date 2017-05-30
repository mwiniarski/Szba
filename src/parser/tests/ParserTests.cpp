#define private public
#include "../Parser.h"
#undef private

#include <sstream>

#include <boost/test/unit_test.hpp>

using namespace parser;
typedef std::istringstream is;

BOOST_AUTO_TEST_SUITE(ParserTests)

BOOST_AUTO_TEST_CASE(parser_check_token)
{
    is in("'hey hello'");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    BOOST_CHECK(parser.checkToken(Token::Type::String));
}

BOOST_AUTO_TEST_CASE(parser_check_many_advance)
{
    is in("var123");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    BOOST_CHECK(parser.checkToken(Token::Type::Ident));
    parser.advance();
    BOOST_CHECK(parser.checkToken(Token::Type::Newline));
    parser.advance();
    BOOST_CHECK(parser.checkToken(Token::Type::Eof));
    parser.advance();
    BOOST_CHECK(parser.checkToken(Token::Type::Eof));
}

BOOST_AUTO_TEST_CASE(parser_check_var)
{
    is in("var123");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    BOOST_CHECK_EQUAL(parser.var()->toString(), "var123");
}

BOOST_AUTO_TEST_CASE(parser_constant_string)
{
    is in("'some string '");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    auto constant = parser.constant();
    BOOST_CHECK(constant->isString());
    BOOST_CHECK_EQUAL(constant->getString(), "some string ");
}

BOOST_AUTO_TEST_CASE(parser_constant_int)
{
    is in("12345");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    auto constant = parser.constant();
    BOOST_CHECK(!constant->isString());
    BOOST_CHECK_EQUAL(constant->getInt(), 12345);
}

BOOST_AUTO_TEST_CASE(parser_require_token)
{
    is in("]");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    parser.requireToken(Token::Type::Rsquare);
}

BOOST_AUTO_TEST_CASE(parser_require_token_throws)
{
    is in("]");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    BOOST_CHECK_THROW(parser.requireToken(Token::Type::Lsquare), std::runtime_error);;
}

BOOST_AUTO_TEST_CASE(parser_oper)
{
    is in("+= =");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    BOOST_CHECK_EQUAL(toString(parser.assignOp()), "+=");
    BOOST_CHECK_EQUAL(toString(parser.assignOp()), "=");
}

BOOST_AUTO_TEST_CASE(parser_factor_constant)
{
    is in("123 'hey!'");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    auto factor = parser.factor();
    BOOST_CHECK_EQUAL(factor->toString(), "123");
    factor = parser.factor();
    BOOST_CHECK_EQUAL(factor->toString(), "hey!");
}

BOOST_AUTO_TEST_CASE(parser_factor_list_one_element)
{
    is in("[123]");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    auto factor = parser.factor();
    BOOST_CHECK_EQUAL(factor->toString(), "123");
}

BOOST_AUTO_TEST_CASE(parser_factor_list)
{
    is in("[123,'a','b','c',65432]");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    auto factor = parser.factor();
    BOOST_CHECK_EQUAL(factor->toString(), "123abc65432");
}

BOOST_AUTO_TEST_CASE(parser_factor_throw_error)
{
    is in("[123,");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    BOOST_CHECK_THROW(parser.factor(), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(parser_operation)
{
    is in("[123] + 'asd' + 321 5");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    BOOST_CHECK_EQUAL(parser.operation()->toString(), "123asd321");
    BOOST_CHECK_EQUAL(parser.operation()->toString(), "5");
}

BOOST_AUTO_TEST_CASE(parser_dictionary_one_item)
{
    is in("(a:5)");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    auto dict = parser.dictionary();
    BOOST_CHECK_EQUAL(dict->toString(), "a5");
}

BOOST_AUTO_TEST_CASE(parser_dictionary)
{
    is in("(a:5,b:'b',c:[1,2,3],d:['a'])");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    auto dict = parser.dictionary();
    BOOST_CHECK_EQUAL(dict->toString(), "a5bbc123da");
}

BOOST_AUTO_TEST_CASE(parser_dictionary_throw_error)
{
    is in("(gre:k)");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    BOOST_CHECK_THROW(parser.dictionary(), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(parser_expression)
{
    is in("aVar 'hey' 123 [124,'a'] (hey:'babe')");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    BOOST_CHECK_EQUAL(parser.expression()->toString(), "aVar");
    BOOST_CHECK_EQUAL(parser.expression()->toString(), "hey");
    BOOST_CHECK_EQUAL(parser.expression()->toString(), "123");
    BOOST_CHECK_EQUAL(parser.expression()->toString(), "124a");
    BOOST_CHECK_EQUAL(parser.expression()->toString(), "heybabe");
}

BOOST_AUTO_TEST_CASE(parser_assignment)
{
    is in("a = b c = 'd' e = 1 f = 5 c += ['oh','my','it'] w += orks"
          " per += (f:'ectly')");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    BOOST_CHECK_EQUAL(parser.assignment()->toString(), "a=b");
    BOOST_CHECK_EQUAL(parser.assignment()->toString(), "c=d");
    BOOST_CHECK_EQUAL(parser.assignment()->toString(), "e=1");
    BOOST_CHECK_EQUAL(parser.assignment()->toString(), "f=5");
    BOOST_CHECK_EQUAL(parser.assignment()->toString(), "c+=ohmyit");
    BOOST_CHECK_EQUAL(parser.assignment()->toString(), "w+=orks");
    BOOST_CHECK_EQUAL(parser.assignment()->toString(), "per+=fectly");
}

BOOST_AUTO_TEST_CASE(parser_statement)
{
    is in("a = b b=c");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    BOOST_CHECK_EQUAL(parser.statement()->toString(), "a=b");
    BOOST_CHECK_EQUAL(parser.statement()->toString(), "b=c");
}

BOOST_AUTO_TEST_CASE(parser_block_with_endlines)
{
    is in("hey += (come:['h','e'],r:'e') \n"
          "I = need \n to += ['test','my', 'parser']");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    BOOST_CHECK_EQUAL(parser.block()->toString(), "hey+=comehereI=needto+=testmyparser");
}

BOOST_AUTO_TEST_CASE(parser_program)
{
    is in("I = need \n to += ['test','my', 'parser'] + 5 + 'heh'");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    BOOST_CHECK_EQUAL(parser.program()->toString(), "I=needto+=testmyparser5heh");
}

BOOST_AUTO_TEST_CASE(parser_relop)
{
    is in("== !=");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    BOOST_CHECK_EQUAL(toString(parser.relOp()), "==");
    BOOST_CHECK_EQUAL(toString(parser.relOp()), "!=");
}

BOOST_AUTO_TEST_CASE(parser_logic_expr)
{
    is in("hello1 'asd' 123");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    BOOST_CHECK_EQUAL(parser.logicExpr()->toString(), "hello1");
    BOOST_CHECK_EQUAL(parser.logicExpr()->toString(), "asd");
    BOOST_CHECK_EQUAL(parser.logicExpr()->toString(), "123");
}

BOOST_AUTO_TEST_CASE(parser_elsestat)
{
    is in("else \n a=6+3");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    BOOST_CHECK_EQUAL(parser.elseStat()->toString(), "a=63");
}

BOOST_AUTO_TEST_CASE(parser_logic_cond)
{
    is in("hello != world ah == oh");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    BOOST_CHECK_EQUAL(parser.logicCond()->toString(), "hello!=world");
    BOOST_CHECK_EQUAL(parser.logicCond()->toString(), "ah==oh");
}

BOOST_AUTO_TEST_CASE(parser_ifstat)
{
    is in("if a==5 : \n b='maj' + 3 \n end");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    BOOST_CHECK_EQUAL(parser.ifStat()->toString(), "a==5b=maj3");
}

BOOST_AUTO_TEST_CASE(parser_ifstat_else)
{
    is in("if a!=5: \n b='maj' + 3 \n else \n b='maj' + 2 \n end");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    BOOST_CHECK_EQUAL(parser.ifStat()->toString(), "a!=5b=maj3b=maj2");
}

BOOST_AUTO_TEST_CASE(parser_if_in_if_in_if)
{
    is in("if a!=5: \n if b!=4: \n if c==3:\n b+=1\n end \nend\n end");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    BOOST_CHECK_EQUAL(parser.ifStat()->toString(), "a!=5b!=4c==3b+=1");
}

BOOST_AUTO_TEST_CASE(parser_program_ultimate1)
{
    is in("a = (a:'b', b:5) \n"
          "if ['a'] == var1:\n"
          "if asd != 'asd': \n"
          "asd += 5\n"
          "end \n"
          "a = 5\n"
          "end");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    BOOST_CHECK_EQUAL(parser.program()->toString(), "a=abb5a==var1asd!=asdasd+=5a=5");
}

BOOST_AUTO_TEST_CASE(parser_while_stat)
{
    is in("while a != b: \n"
          "a+=1\n"
          "end");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    BOOST_CHECK_EQUAL(parser.whileStat()->toString(), "a!=ba+=1");
}

BOOST_AUTO_TEST_CASE(parser_print_stat)
{
    is in("Print('Hello world') Print(123)");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    BOOST_CHECK_EQUAL(parser.printStat()->toString(), "Hello world");
    BOOST_CHECK_EQUAL(parser.printStat()->toString(), "123");
}

BOOST_AUTO_TEST_CASE(parser_exec_stat)
{
    is in("Program((a:'b'), ['a','b'], 555)");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    BOOST_CHECK_EQUAL(parser.execStat()->toString(), "progabab555");
}

BOOST_AUTO_TEST_CASE(parser_func_def)
{
    is in("def funkcja():\n a+=5 \n end def asd(a,b,c):\n if a==5:\n a+=1\n end\n end");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    BOOST_CHECK_EQUAL(parser.funcDef()->toString(), "funkcjaa+=5");
    BOOST_CHECK_EQUAL(parser.funcDef()->toString(), "asdabca==5a+=1");
}

BOOST_AUTO_TEST_CASE(parser_func_invoke)
{
    is in("fun funkcja() fun asd((a:'6'), 4)");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    BOOST_CHECK_EQUAL(parser.funcInvoke()->toString(), "funkcja");
    BOOST_CHECK_EQUAL(parser.funcInvoke()->toString(), "asda64");
}



































BOOST_AUTO_TEST_SUITE_END()
