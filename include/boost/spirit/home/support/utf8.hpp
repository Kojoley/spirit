/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_SPIRIT_UC_TYPES_NOVEMBER_23_2008_0840PM)
#define BOOST_SPIRIT_UC_TYPES_NOVEMBER_23_2008_0840PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>
#include <boost/cstdint.hpp>
#include <boost/foreach.hpp>
#include <boost/regex/pending/unicode_iterator.hpp>
#include <boost/type_traits/make_unsigned.hpp>
#include <string>

namespace boost { namespace spirit
{
    typedef ::boost::uint32_t ucs4_char;
    typedef char utf8_char;
    typedef std::basic_string<ucs4_char> ucs4_string;
    typedef std::basic_string<utf8_char> utf8_string;

namespace detail2
{

namespace encoding
{

enum encoding
{
    utf8,
    utf16,
    utf32,
    unknown
};

}

namespace traits
{

template <typename Char>
struct char_encoding;

// FIXME: info::info should not rely on this
template <>
struct char_encoding<char>
{
    static encoding::encoding const value = encoding::utf32;
};

#ifdef __cpp_char8_t
template <>
struct char_encoding<char8_t>
{
    static encoding::encoding const value = encoding::utf8;
};
#endif

#ifndef BOOST_NO_CXX11_CHAR16_T
template <>
struct char_encoding<char16_t>
{
    static encoding::encoding const value = encoding::utf16;
};
#endif

#ifndef BOOST_NO_CXX11_CHAR32_T
template <>
struct char_encoding<char32_t>
{
    static encoding::encoding const value = encoding::utf32;
};
#endif

#ifndef BOOST_NO_CXX11_UNICODE_LITERALS
template <>
struct char_encoding<wchar_t>
{
private:
    static make_unsigned<wchar_t>::type const uwcp = L"\U0010FFFF"[0];
    static unsigned char const u8cp = u8"\U0010FFFF"[0];

public:
    static_assert(U"\U0010FFFF"[0] != u"\U0010FFFF"[0], "");
    static_assert(U"\U0010FFFF"[0] != u8cp, "");

    static encoding::encoding const value =
        uwcp == U"\U0010FFFF"[0] ? encoding::utf32
      : uwcp == u"\U0010FFFF"[0] ? encoding::utf16
      : uwcp == u8cp ? encoding::utf8
      : encoding::unknown;
};
#else
#if defined(_MSC_VER) && _MSC_VER < 1700
# pragma warning(push)
// In MSVC < 11 this has to be out of the class to have any effect
# pragma warning(disable: 4428) // universal-character-name encountered in source
#endif
template <>
struct char_encoding<wchar_t>
{
    static encoding::encoding const value =
        sizeof(L"\U0010FFFF") / sizeof(wchar_t) == 2 ? encoding::utf32
      : sizeof(L"\uFFFF") / sizeof(wchar_t) == 2 ? encoding::utf16
      : encoding::unknown;
};
#if defined(_MSC_VER) && _MSC_VER < 1700
# pragma warning(pop)
#endif
#endif

template <>
struct char_encoding<ucs4_char>
{
    static encoding::encoding const value = encoding::utf32;
};

} // namespace traits


template <encoding::encoding Encoding>
struct string_conversion;

template <>
struct string_conversion<encoding::utf32>
{
    template <typename Char>
    static utf8_string to_utf8(Char value)
    {
        // always store as UTF8
        utf8_string result;
        typedef std::back_insert_iterator<utf8_string> insert_iter;
        insert_iter out_iter(result);
        utf8_output_iterator<insert_iter> utf8_iter(out_iter);
        typedef typename make_unsigned<Char>::type UChar;
        *utf8_iter = (UChar)value;
        return result;
    }

    template <typename Char>
    static utf8_string to_utf8(Char const* str)
    {
        // always store as UTF8
        utf8_string result;
        typedef std::back_insert_iterator<utf8_string> insert_iter;
        insert_iter out_iter(result);
        utf8_output_iterator<insert_iter> utf8_iter(out_iter);
        typedef typename make_unsigned<Char>::type UChar;
        while (*str)
            *utf8_iter++ = (UChar)*str++;
        return result;
    }

    template <typename Char, typename Traits, typename Allocator>
    static utf8_string
    to_utf8(std::basic_string<Char, Traits, Allocator> const& str)
    {
        // always store as UTF8
        utf8_string result;
        typedef std::back_insert_iterator<utf8_string> insert_iter;
        insert_iter out_iter(result);
        utf8_output_iterator<insert_iter> utf8_iter(out_iter);
        typedef typename make_unsigned<Char>::type UChar;
        BOOST_FOREACH(Char ch, str)
        {
            *utf8_iter++ = (UChar)ch;
        }
        return result;
    }
};

template <>
struct string_conversion<encoding::utf16>
{
    template <typename Char>
    static utf8_string to_utf8(Char value)
    {
        utf8_string result;
        typedef std::back_insert_iterator<utf8_string> insert_iter;
        insert_iter out_iter(result);
        utf8_output_iterator<insert_iter> utf8_iter(out_iter);

        u16_to_u32_iterator<Char const*, ucs4_char> ucs4_iter(&value);
        *utf8_iter++ = *ucs4_iter;

        return result;
    }

    template <typename Char>
    static utf8_string to_utf8(Char const* str)
    {
        utf8_string result;
        typedef std::back_insert_iterator<utf8_string> insert_iter;
        insert_iter out_iter(result);
        utf8_output_iterator<insert_iter> utf8_iter(out_iter);

        u16_to_u32_iterator<Char const*, ucs4_char> ucs4_iter(str);
        for (ucs4_char c; (c = *ucs4_iter) != ucs4_char(); ++ucs4_iter) {
            *utf8_iter++ = c;
        }

        return result;
    }

    template <typename Char, typename Traits, typename Allocator>
    static utf8_string
    to_utf8(std::basic_string<Char, Traits, Allocator> const& str)
    {
        return to_utf8(str.c_str());
    }
};

template <>
struct string_conversion<encoding::utf8>
{
#if 0 // TODO: when utf8_char will be char8_t
    static utf8_string to_utf8(utf8_string str)
    {
        return str;
    }
#else
    template <typename Char>
    static utf8_string to_utf8(Char value)
    {
        return utf8_string(1, value);
    }

    template <typename Char>
    static utf8_string to_utf8(Char const* str)
    {
        return utf8_string(str);
    }

    template <typename Char, typename Traits, typename Allocator>
    static utf8_string
    to_utf8(std::basic_string<Char, Traits, Allocator> const& str)
    {
        return utf8_string(str.begin(), str.end());
    }
#endif
};

} // namespace detail2

    template <typename Char>
    inline utf8_string to_utf8(Char value)
    {
        return detail2::string_conversion<detail2::traits::char_encoding<Char>::value>::to_utf8(value);
    }

    template <typename Char>
    inline utf8_string to_utf8(Char const* str)
    {
        return detail2::string_conversion<detail2::traits::char_encoding<Char>::value>::to_utf8(str);
    }

    template <typename Char, typename Traits, typename Allocator>
    inline utf8_string
    to_utf8(std::basic_string<Char, Traits, Allocator> const& str)
    {
        return detail2::string_conversion<detail2::traits::char_encoding<Char>::value>::to_utf8(str);
    }
}}

#endif
