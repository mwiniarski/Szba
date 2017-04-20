#include "../Scanner.h"
#include "../Source.h"

#include <sstream>

#include <boost/test/unit_test.hpp>

using namespace parser;

BOOST_AUTO_TEST_SUITE(ScannerTests)

BOOST_AUTO_TEST_CASE(scanner_gets_source_arg_in_contstructor)
{
    Source s(std::istringstream in("a"));

    BOOST_CHECK_EQUAL(s.nextChar(), '\n');
    BOOST_CHECK_EQUAL(s.nextChar(), EOF);
}

BOOST_AUTO_TEST_SUITE_END()
