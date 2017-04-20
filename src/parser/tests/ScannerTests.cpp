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

BOOST_AUTO_TEST_SUITE_END()
