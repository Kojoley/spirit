/*=============================================================================
    Copyright (c) 2018 Nikita Kniazev

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_SUPPORT_COMPAT_FUNCTION_NOV_17_2018_0204PM)
#define BOOST_SPIRIT_SUPPORT_COMPAT_FUNCTION_NOV_17_2018_0204PM

#include <boost/config.hpp>

#if !defined(BOOST_SPIRIT_NO_STD_FUNCTION) && defined(BOOST_NO_CXX11_HDR_FUNCTIONAL)
#  define BOOST_SPIRIT_NO_STD_FUNCTION
#endif

namespace boost { namespace spirit { namespace compat
{
#ifndef BOOST_SPIRIT_NO_STD_FUNCTION
#  include <functional>
   using ::std::function;
#else
#  include <boost/function.hpp>
   using ::boost::function;
#endif
}}}

#endif
