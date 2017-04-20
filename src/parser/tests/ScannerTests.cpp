#include "../Scanner.h"

#include <sstream>

#include <boost/test/unit_test.hpp>

using namespace parser;

BOOST_AUTO_TEST_SUITE(ScannerTests)

BOOST_AUTO_TEST_CASE(reading_token_before_first_advance_returns_eof)
{
    std::istringstream in;
    Scanner s(in);
    BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Eof);
}

BOOST_AUTO_TEST_CASE(scanning_empty_input_returns_eof_token)
{
    std::istringstream in;
    Scanner s(in);
    s.readNextToken();

    BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Eof);
}

BOOST_AUTO_TEST_CASE(scanner_read_int_token)
{
    std::istringstream in("123");
    Scanner s(in);

    s.readNextToken();
    const auto t = s.getToken();

    BOOST_CHECK_EQUAL(t.getType(), Token::Type::Integer);
    BOOST_CHECK_EQUAL(t.getInteger(), 123);
}

BOOST_AUTO_TEST_CASE(scanner_returns_eof_after_last_token)
{
    std::istringstream in("123");
    Scanner s(in);

    s.readNextToken();
    s.readNextToken();

    BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Eof);
}

BOOST_AUTO_TEST_CASE(scanner_ignores_whitespaces)
{
    std::istringstream in("    \t\n     123");
    Scanner s(in);

    s.readNextToken();
    const auto t = s.getToken();

    BOOST_CHECK_EQUAL(t.getType(), Token::Type::Integer);
    BOOST_CHECK_EQUAL(t.getInteger(), 123);
}

BOOST_AUTO_TEST_CASE(scanner_throws_on_unknown_token)
{
    std::istringstream in("x");
    Scanner s(in);

    BOOST_CHECK_THROW(s.readNextToken(), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(scanner_reads_subsequent_tokens)
{
    std::istringstream in("12 100");
    Scanner s(in);

    s.readNextToken();
    const auto t1 = s.getToken();

    s.readNextToken();
    const auto t2 = s.getToken();

    s.readNextToken();
    const auto t3 = s.getToken();

    BOOST_CHECK_EQUAL(t1.getType(), Token::Type::Integer);
    BOOST_CHECK_EQUAL(t2.getType(), Token::Type::Integer);
    BOOST_CHECK_EQUAL(t3.getType(), Token::Type::Eof);

    BOOST_CHECK_EQUAL(t1.getInteger(), 12);
    BOOST_CHECK_EQUAL(t2.getInteger(), 100);
}

BOOST_AUTO_TEST_CASE(scanner_throws_on_stream_error)
{
    std::istringstream in("123");
    in.setstate(std::ios_base::badbit);
    Scanner s(in);

    BOOST_CHECK_THROW(s.readNextToken(), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(scanner_scans_plus_operator_properly)
{
    std::istringstream in("+");
    Scanner s(in);
    s.readNextToken();

    BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Operator);
    BOOST_CHECK_EQUAL(s.getToken().getOperator(), ast::Operator::Plus);
}

BOOST_AUTO_TEST_CASE(scanner_scans_minus_operator_properly)
{
    std::istringstream in("-");
    Scanner s(in);
    s.readNextToken();

    BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Operator);
    BOOST_CHECK_EQUAL(s.getToken().getOperator(), ast::Operator::Minus);
}

BOOST_AUTO_TEST_SUITE_END()
