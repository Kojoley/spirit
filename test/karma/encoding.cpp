//  Copyright (c) 2001-2011 Hartmut Kaiser
//  Copyright (c) 2001-2011 Joel de Guzman
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// this file intentionally contains non-ascii characters
// boostinspect:noascii

#include <boost/detail/lightweight_test.hpp>
#include <boost/spirit/include/karma_char.hpp>
#include <boost/spirit/include/karma_string.hpp>
#include <boost/spirit/include/karma_directive.hpp>
#include <boost/spirit/include/karma_action.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <iostream>
#include "test.hpp"

int
main()
{
    using spirit_test::test;
    using boost::spirit::karma::lit;
    using boost::spirit::karma::lower;
    using boost::spirit::karma::upper;
    using boost::spirit::karma::char_;
    using boost::spirit::karma::encoding;
    namespace char_encoding = boost::spirit::char_encoding;

    encoding<char_encoding::iso8859_1> iso8859_1;

// needed for VC7.1 only
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1310))
#pragma setlocale("french")
#endif

    {
        BOOST_TEST(test("\xE1", iso8859_1[lower['\xE1']]));
        BOOST_TEST(test("\xC1", iso8859_1[upper['\xE1']]));
        BOOST_TEST(test("\xE1", iso8859_1[lower[char_('\xE1')]]));
        BOOST_TEST(test("\xC1", iso8859_1[upper[char_('\xE1')]]));
        BOOST_TEST(test("\xE1", iso8859_1[lower[lit('\xE1')]]));
        BOOST_TEST(test("\xC1", iso8859_1[upper[lit('\xE1')]]));
        BOOST_TEST(test("\xE1", iso8859_1[lower[char_]], '\xE1'));
        BOOST_TEST(test("\xC1", iso8859_1[upper[char_]], '\xE1'));
        BOOST_TEST(test("\xE1", iso8859_1[lower['\xC1']]));
        BOOST_TEST(test("\xC1", iso8859_1[upper['\xC1']]));
        BOOST_TEST(test("\xE1", iso8859_1[lower[char_('\xC1')]]));
        BOOST_TEST(test("\xC1", iso8859_1[upper[char_('\xC1')]]));
        BOOST_TEST(test("\xE1", iso8859_1[lower[lit('\xC1')]]));
        BOOST_TEST(test("\xC1", iso8859_1[upper[lit('\xC1')]]));
        BOOST_TEST(test("\xE1", iso8859_1[lower[char_]], '\xC1'));
        BOOST_TEST(test("\xC1", iso8859_1[upper[char_]], '\xC1'));
    }

#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1310))
#pragma setlocale("")
#endif

// needed for VC7.1 only
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1310))
#pragma setlocale("german")
#endif
    {
        BOOST_TEST(test("\xE4\xE4", iso8859_1[lower["\xC4\xE4"]]));
        BOOST_TEST(test("\xE4\xE4", iso8859_1[lower[lit("\xC4\xE4")]]));

        BOOST_TEST(test("\xC4\xC4", iso8859_1[upper["\xC4\xE4"]]));
        BOOST_TEST(test("\xC4\xC4", iso8859_1[upper[lit("\xC4\xE4")]]));
    }
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1310))
#pragma setlocale("")
#endif

    return boost::report_errors();
}
