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
    BOOST_CHECK_EQUAL(ast::toString(parser.oper()), "+=");
    BOOST_CHECK_EQUAL(ast::toString(parser.oper()), "=");
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

BOOST_AUTO_TEST_CASE(parser_statement_with_endline)
{
    is in("a = b \n b=c");
    Parser parser(std::make_unique<Scanner>(
        std::make_unique<Source>(in)));
    parser.advance();
    BOOST_CHECK_EQUAL(parser.statement()->toString(), "a=b");
    BOOST_CHECK_EQUAL(parser.statement()->toString(), "b=c");
}

BOOST_AUTO_TEST_CASE(parser_block)
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

BOOST_AUTO_TEST_SUITE_END()
