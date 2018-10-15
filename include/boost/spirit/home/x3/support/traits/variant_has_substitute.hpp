/*=============================================================================
    Copyright (c) 2001-2014 Joel de Guzman
    http://spirit.sourceforge.net/

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_X3_VARIANT_HAS_SUBSTITUTE_APR_18_2014_925AM)
#define BOOST_SPIRIT_X3_VARIANT_HAS_SUBSTITUTE_APR_18_2014_925AM

#include <boost/spirit/home/x3/support/traits/is_substitute.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/declval.hpp>

namespace boost { namespace spirit { namespace x3 { namespace traits
{
    template <typename Variant, typename Attribute, typename Enabled = void>
    struct variant_has_substitute_impl : mpl::false_ {};
    template <typename Variant, typename Attribute>
    struct variant_has_substitute_impl<Variant, Attribute, decltype(void(Variant{boost::declval<Attribute>()}))> : mpl::true_ {};

    template <typename Variant, typename Attribute>
    struct variant_has_substitute
        : variant_has_substitute_impl<Variant, Attribute>::type {};

    template <typename Attribute>
    struct variant_has_substitute<unused_type, Attribute> : mpl::true_ {};

    template <typename Attribute>
    struct variant_has_substitute<unused_type const, Attribute> : mpl::true_ {};

}}}}

#endif
