#include "../Token.h"

#include <sstream>

#include <boost/test/unit_test.hpp>

using namespace parser;

BOOST_AUTO_TEST_SUITE(TokenTests)

BOOST_AUTO_TEST_CASE(default_token_has_not_init_type)
{
    Token t;
    BOOST_CHECK_EQUAL(t.getType(), Token::Type::None);
}

BOOST_AUTO_TEST_CASE(constructor_set_type_properly)
{
    Token t(Token::Type::False);
    BOOST_CHECK_EQUAL(t.getType(), Token::Type::False);
}

BOOST_AUTO_TEST_CASE(constructor_set_int_properly)
{
    Token t(124);
    BOOST_CHECK_EQUAL(t.getNumber(), 124);
}

BOOST_AUTO_TEST_CASE(constructor_set_string_properly)
{
    Token t(Token::Type::Ident, "randomIdent");
    BOOST_CHECK_EQUAL(t.getString(), "randomIdent");
}

BOOST_AUTO_TEST_CASE(token_names_match_string_types)
{
    Token t1(Token::Type::Ident);
    BOOST_CHECK_EQUAL(Token::findToken("Ident"), t1.getType());
    Token t2(Token::Type::Else);
    BOOST_CHECK_EQUAL(Token::findToken("Else"), t2.getType());
    Token t3(Token::Type::And);
    BOOST_CHECK_EQUAL(Token::findToken("And"), t3.getType());
}

BOOST_AUTO_TEST_CASE(wrong_atom_name_gives_none_type)
{
    BOOST_CHECK_EQUAL(Token::findToken("sdfg"), Token::Type::None);
}

BOOST_AUTO_TEST_CASE(assigning_string_to_wrong_type_throws_exception)
{
    BOOST_CHECK_THROW(Token(Token::Type::False, "hello"), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(getting_int_from_wrong_type_throws_exception)
{
    Token t1(Token::Type::False);
    BOOST_CHECK_THROW(t1.getNumber(), std::runtime_error);
}

BOOST_AUTO_TEST_SUITE_END()
