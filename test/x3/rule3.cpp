/*=============================================================================
    Copyright (c) 2001-2012 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// this file deliberately contains non-ascii characters
// boostinspect:noascii

#include <boost/detail/lightweight_test.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/include/std_pair.hpp>

#include <string>
#include <cstring>
#include <iostream>
#include "test.hpp"


struct op_counter
{
    op_counter() : i{}, j{} { ++default_costructed; }
    // TODO: fix unneded move in alternative and make move assignment deleted
    op_counter& operator=(op_counter&&)
    { std::abort(); return *this; }

    int i, j;
    static int default_costructed;
};
static_assert(!std::is_move_constructible<op_counter>::value, "");

int op_counter::default_costructed = 0;

BOOST_FUSION_ADAPT_STRUCT(op_counter, i, j)


using boost::spirit::x3::_val;

struct f
{
    template <typename Context>
    void operator()(Context const& ctx) const
    {
        _val(ctx) += _attr(ctx);
    }
};

int main()
{
    using spirit_test::test_attr;
    using spirit_test::test;

    using namespace boost::spirit::x3::ascii;
    using boost::spirit::x3::rule;
    using boost::spirit::x3::int_;
    using boost::spirit::x3::lit;
    using boost::spirit::x3::eps;


    { // synth attribute value-init

        std::string s;
        typedef rule<class r, std::string> rule_type;

        auto rdef = rule_type()
            = alpha                 [f()]
            ;

        BOOST_TEST(test_attr("abcdef", +rdef, s));
        BOOST_TEST(s == "abcdef");
    }

    { // synth attribute value-init

        std::string s;
        typedef rule<class r, std::string> rule_type;

        auto rdef = rule_type() =
            alpha /
               [](auto& ctx)
               {
                  _val(ctx) += _attr(ctx);
               }
            ;

        BOOST_TEST(test_attr("abcdef", +rdef, s));
        BOOST_TEST(s == "abcdef");
    }

    { // ensure no unneded synthesization, copying and moving occured
        auto a = rule<class a_r, op_counter>{} = '{' >> int_ >> ':' >> int_ >> '}';
        auto b = rule<class b_r, op_counter>{} = eps >> (a | a);
        auto c = rule<class c_r, op_counter, true>{} = eps >> (a[([] {})] | a);

        BOOST_TEST(test("{123:456}", b));
        // TODO: can be reduced to zero if remove synthesization for rcontext while actual attr is unused
        BOOST_TEST_EQ(boost::exchange(op_counter::default_costructed, 0), 1);
        BOOST_TEST(test("{123:456}", c));
        // TODO: can be reduced to zero if remove synthesization for rcontext while actual attr is unused
        BOOST_TEST_EQ(boost::exchange(op_counter::default_costructed, 0), 1);

        op_counter oc;
        BOOST_TEST_EQ(boost::exchange(op_counter::default_costructed, 0), 1);
        BOOST_TEST(test_attr("{123:456}", b, oc));
        BOOST_TEST(test_attr("{123:456}", b[([] {})], oc));
        BOOST_TEST(test_attr("{123:456}", c, oc));
        BOOST_TEST(test_attr("{123:456}", c[([] {})], oc));
        BOOST_TEST_EQ(boost::exchange(op_counter::default_costructed, 0), 0);
    }

    return boost::report_errors();
}
