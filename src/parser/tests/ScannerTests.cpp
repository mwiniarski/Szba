#include "../Scanner.h"
#include "../Source.h"

#include <sstream>

#include <boost/test/unit_test.hpp>

using namespace parser;

BOOST_AUTO_TEST_SUITE(ScannerTests)

BOOST_AUTO_TEST_CASE(scanner_multiple_eofs)
{
    std::istringstream in("var123");
    auto s = std::make_unique<Scanner>(std::make_unique<Source>(in));
    s->readNextToken();
    s->readNextToken();
    s->readNextToken();
    BOOST_CHECK_EQUAL(s->getToken().getType(), Token::Type::Eof);
    s->readNextToken();
    BOOST_CHECK_EQUAL(s->getToken().getType(), Token::Type::Eof);

}

BOOST_AUTO_TEST_CASE(scanner_gets_source_arg_in_contstructor)
{
    std::istringstream in;
    Scanner s(std::make_unique<Source>(in));
    BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::None);
}

BOOST_AUTO_TEST_CASE(scanner_reach_eof_after_reading_only_whitespaces)
{
    std::istringstream in("  ");
    Scanner s(std::make_unique<Source>(in));
    s.readNextToken();
    BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Newline);
    s.readNextToken();
    BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Eof);
}

BOOST_AUTO_TEST_CASE(scanner_identify_ident)
{
    std::istringstream in("  var123[]");
    Scanner s(std::make_unique<Source>(in));
    s.readNextToken();
    BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Ident);
    BOOST_CHECK_EQUAL(s.getToken().getString(), "var123");
}

BOOST_AUTO_TEST_CASE(scanner_identify_int)
{
    std::istringstream in("234");
    Scanner s(std::make_unique<Source>(in));
    s.readNextToken();
    BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Int);
    BOOST_CHECK_EQUAL(s.getToken().getNumber(), 234);
}

BOOST_AUTO_TEST_CASE(scanner_number_too_large)
{
    std::istringstream in("1234567890");
    Scanner s(std::make_unique<Source>(in));
    BOOST_CHECK_THROW(s.readNextToken(), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(scanner_identify_string)
{
    std::istringstream in("'tralala'");
    Scanner s(std::make_unique<Source>(in));
    s.readNextToken();
    BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::String);
    BOOST_CHECK_EQUAL(s.getToken().getString(), "tralala");
}

BOOST_AUTO_TEST_CASE(scanner_ultimate_test)
{
    std::istringstream in("[]+=)=:\n;asd Def 345 'hehe'");
    Scanner s(std::make_unique<Source>(in));
    s.readNextToken();
    BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Lsquare);
    s.readNextToken();
    BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Rsquare);
    s.readNextToken();
    BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Pluseq);
    s.readNextToken();
    BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Rbra);
    s.readNextToken();
    BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Eq);
    s.readNextToken();
    BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Colon);
    s.readNextToken();
    BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Newline);
    s.readNextToken();
    BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Semic);
    s.readNextToken();
    BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Ident);
    BOOST_CHECK_EQUAL(s.getToken().getString(), "asd");
    s.readNextToken();
    BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Def);
    s.readNextToken();
    BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Int);
    BOOST_CHECK_EQUAL(s.getToken().getNumber(), 345);
    s.readNextToken();
    BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::String);
    BOOST_CHECK_EQUAL(s.getToken().getString(), "hehe");
    s.readNextToken();
    BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Newline);
    s.readNextToken();
    BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Eof);
}

BOOST_AUTO_TEST_CASE(scanner_eq_test)
{
    std::istringstream in("+= =");
    auto s = std::make_unique<Scanner>(std::make_unique<Source>(in));
    s->readNextToken();
    BOOST_CHECK_EQUAL(s->getToken().getType(), Token::Type::Pluseq);
    s->readNextToken();
    BOOST_CHECK_EQUAL(s->getToken().getType(), Token::Type::Eq);
}

BOOST_AUTO_TEST_SUITE_END()
