/*=============================================================================
    Copyright (c) 2018-2020 Nikita Kniazev

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include <boost/core/lightweight_test.hpp>
#include <boost/spirit/home/support/utf8.hpp>
#include <string>

#if defined(_MSC_VER) && _MSC_VER < 1700
# pragma warning(disable: 4428) // universal-character-name encountered in source
#endif

int main()
{
    using boost::spirit::to_utf8;

#ifdef __cpp_char8_t
    using namespace std::string_literals;

    BOOST_TEST_CSTR_EQ("\xF0\x9F\xA7\x90\xF0\x9F\xA7\xA0",
                       to_utf8(u8"\U0001F9D0\U0001F9E0").c_str());
    BOOST_TEST_CSTR_EQ("\xF0\x9F\xA7\x90\xF0\x9F\xA7\xA0",
                       to_utf8(u8"\U0001F9D0\U0001F9E0"s).c_str());
#endif

    BOOST_TEST_CSTR_EQ("\xEF\xBF\xA1", to_utf8(L'\uFFE1').c_str());
    BOOST_TEST_CSTR_EQ("\xF0\x9F\xA7\x90\xF0\x9F\xA7\xA0",
                       to_utf8(L"\U0001F9D0\U0001F9E0").c_str());
    BOOST_TEST_CSTR_EQ("\xF0\x9F\xA7\x90\xF0\x9F\xA7\xA0",
                       to_utf8(std::wstring(L"\U0001F9D0\U0001F9E0")).c_str());

#ifndef BOOST_NO_CXX11_UNICODE_LITERALS
#ifndef BOOST_NO_CXX11_CHAR16_T
    BOOST_TEST_CSTR_EQ("\xEF\xBF\xA1", to_utf8(u'\uFFE1').c_str());
    BOOST_TEST_CSTR_EQ("\xF0\x9F\xA7\x90\xF0\x9F\xA7\xA0",
                       to_utf8(u"\U0001F9D0\U0001F9E0").c_str());
    BOOST_TEST_CSTR_EQ("\xF0\x9F\xA7\x90\xF0\x9F\xA7\xA0",
                       to_utf8(std::u16string(u"\U0001F9D0\U0001F9E0")).c_str());
#endif

#ifndef BOOST_NO_CXX11_CHAR32_T
    BOOST_TEST_CSTR_EQ("\xEF\xBF\xA1", to_utf8(U'\uFFE1').c_str());
    BOOST_TEST_CSTR_EQ("\xF0\x9F\xA7\x90", to_utf8(U'\U0001F9D0').c_str());
    BOOST_TEST_CSTR_EQ("\xF0\x9F\xA7\x90\xF0\x9F\xA7\xA0",
                       to_utf8(U"\U0001F9D0\U0001F9E0").c_str());
    BOOST_TEST_CSTR_EQ("\xF0\x9F\xA7\x90\xF0\x9F\xA7\xA0",
                       to_utf8(std::u32string(U"\U0001F9D0\U0001F9E0")).c_str());
#endif
#endif

    return boost::report_errors();
}
