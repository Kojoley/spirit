/*=============================================================================
    Copyright (c) 2001-2014 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_SPIRIT_X3_UC_TYPES_NOVEMBER_23_2008_0840PM)
#define BOOST_SPIRIT_X3_UC_TYPES_NOVEMBER_23_2008_0840PM

#include <boost/cstdint.hpp>
#include <boost/regex/pending/unicode_iterator.hpp>
#include <boost/type_traits/make_unsigned.hpp>
#include <string>

namespace boost { namespace spirit { namespace x3
{
    typedef ::boost::uint32_t ucs4_char;
    typedef char utf8_char;
    typedef std::basic_string<ucs4_char> ucs4_string;
    typedef std::basic_string<utf8_char> utf8_string;

namespace detail2
{

enum class encoding
{
    utf8,
    utf16,
    utf32,
    unknown,
};

namespace traits
{

template <typename Char>
struct char_encoding;

// FIXME: get_info<literal_string<...>> should not rely on this
template <>
struct char_encoding<char>
{
    static encoding const value = encoding::utf32;
};

#ifdef __cpp_char8_t
template <>
struct char_encoding<char8_t>
{
    static encoding const value = encoding::utf8;
};
#endif

template <>
struct char_encoding<char16_t>
{
    static encoding const value = encoding::utf16;
};

template <>
struct char_encoding<char32_t>
{
    static encoding const value = encoding::utf32;
};

template <>
struct char_encoding<wchar_t>
{
private:
    static make_unsigned<wchar_t>::type const uwcp = L"\U0010FFFF"[0];
    static unsigned char const u8cp = u8"\U0010FFFF"[0];

public:
    static_assert(U"\U0010FFFF"[0] != u"\U0010FFFF"[0], "");
    static_assert(U"\U0010FFFF"[0] != u8cp, "");

    static encoding const value =
        uwcp == U"\U0010FFFF"[0] ? encoding::utf32
      : uwcp == u"\U0010FFFF"[0] ? encoding::utf16
      : uwcp == u8cp ? encoding::utf8
      : encoding::unknown;
};

template <>
struct char_encoding<ucs4_char>
{
    static encoding const value = encoding::utf32;
};

} // namespace traits


template <encoding Encoding>
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
        for (Char ch : str)
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
        return { 1, value };
    }

    template <typename Char>
    static utf8_string to_utf8(Char const* str)
    {
        return { str };
    }

    template <typename Char, typename Traits, typename Allocator>
    static utf8_string
    to_utf8(std::basic_string<Char, Traits, Allocator> const& str)
    {
        return { str.begin(), str.end() };
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
}}}

#endif
