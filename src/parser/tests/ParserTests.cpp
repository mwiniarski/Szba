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
    BOOST_CHECK_EQUAL(parser.var(), "var123");
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
    BOOST_CHECK(parser.oper() == Operator::PlusEq);
    BOOST_CHECK(parser.oper() == Operator::Eq);
}

BOOST_AUTO_TEST_SUITE_END()
