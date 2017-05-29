#include "../Source.h"

#include <sstream>

#include <boost/test/unit_test.hpp>

using namespace parser;

BOOST_AUTO_TEST_SUITE(SourceTests)

BOOST_AUTO_TEST_CASE(nextchar_returns_endline_and_eof_with_empty_stream)
{
    std::istringstream in;
    Source s(in);
    BOOST_CHECK_EQUAL(s.nextChar(), '\n');
    BOOST_CHECK_EQUAL(s.nextChar(), EOF);
}

BOOST_AUTO_TEST_CASE(nextchar_return_correct_characters)
{
    std::istringstream in("AB");
    Source s(in);
    BOOST_CHECK_EQUAL(s.nextChar(), 'A');
    BOOST_CHECK_EQUAL(s.nextChar(), 'B');
}

BOOST_AUTO_TEST_CASE(nextchar_return_correct_whitespaces)
{
    std::istringstream in("  ");
    Source s(in);
    BOOST_CHECK_EQUAL(s.nextChar(), ' ');
    BOOST_CHECK_EQUAL(s.nextChar(), ' ');
}

BOOST_AUTO_TEST_CASE(nextchar_handles_spaces_and_nextlines)
{
    std::istringstream in("A \n B");
    Source s(in);
    BOOST_CHECK_EQUAL(s.nextChar(), 'A');
    BOOST_CHECK_EQUAL(s.nextChar(), ' ');
    BOOST_CHECK_EQUAL(s.nextChar(), '\n');
    BOOST_CHECK_EQUAL(s.nextChar(), ' ');
    BOOST_CHECK_EQUAL(s.nextChar(), 'B');
    BOOST_CHECK_EQUAL(s.nextChar(), '\n');
    BOOST_CHECK_EQUAL(s.nextChar(), -1);
    BOOST_CHECK_EQUAL(s.nextChar(), -1);
}

BOOST_AUTO_TEST_SUITE_END()
