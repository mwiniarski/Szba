#include "../Token.h"

#include <sstream>

#include <boost/test/unit_test.hpp>

using namespace parser;

BOOST_AUTO_TEST_SUITE(TokenTests)

BOOST_AUTO_TEST_CASE(default_token_has_eof_type)
{
    Token t;
    BOOST_CHECK_EQUAL(t.getType(), Token::Type::Eof);
}

BOOST_AUTO_TEST_SUITE_END()
