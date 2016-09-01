/*=============================================================================
    Copyright (c) 2011 Jan Frederick Eick

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#if !defined(BOOST_SPIRIT_TEST_QI_UINT4_HPP)
#define BOOST_SPIRIT_TEST_QI_UINT4_HPP

///////////////////////////////////////////////////////////////////////////////
//
//  *** BEWARE PLATFORM DEPENDENT!!! ***
//  *** The following assumes 32 bit integers and 64 bit long longs.
//  *** Modify these constant strings when appropriate.
//
///////////////////////////////////////////////////////////////////////////////

static char const* max_unsigned_base3 =         "102002022201221111210";
static char const* unsigned_overflow_base3 =    "102002022201221111211";
static char const* digit_overflow_base3 =       "1020020222012211112100";

static char const* max_unsigned_base4 =         "3333333333333333";
static char const* digit_overflow_base4 =       "33333333333333330";

static char const* max_unsigned_base5 =         "32244002423140";
static char const* unsigned_overflow_base5 =    "32244002423141";
static char const* digit_overflow_base5 =       "322440024231400";

static char const* max_unsigned_base6 =         "1550104015503";
static char const* unsigned_overflow_base6 =    "1550104015504";
static char const* digit_overflow_base6 =       "15501040155030";

static char const* max_unsigned_base7 =         "211301422353";
static char const* unsigned_overflow_base7 =    "211301422354";
static char const* digit_overflow_base7 =       "2113014223530";

static char const* max_unsigned_base9 =         "12068657453";
static char const* unsigned_overflow_base9 =    "12068657454";
static char const* digit_overflow_base9 =       "120686574530";

static char const* max_unsigned_base11 =        "1904440553";
static char const* unsigned_overflow_base11 =   "1904440554";
static char const* digit_overflow_base11 =      "19044405530";

static char const* max_unsigned_base12 =        "9BA461593";
static char const* unsigned_overflow_base12 =   "9BA461594";
static char const* digit_overflow_base12 =      "9BA4615930";

static char const* max_unsigned_base13 =        "535A79888";
static char const* unsigned_overflow_base13 =   "535A79889";
static char const* digit_overflow_base13 =      "535A798880";

static char const* max_unsigned_base14 =        "2CA5B7463";
static char const* unsigned_overflow_base14 =   "2CA5B7464";
static char const* digit_overflow_base14 =      "2CA5B74630";

static char const* max_unsigned_base15 =        "1A20DCD80";
static char const* unsigned_overflow_base15 =   "1A20DCD81";
static char const* digit_overflow_base15 =      "1A20DCD800";

static char const* max_unsigned_base17 =        "A7FFDA90";
static char const* unsigned_overflow_base17 =   "A7FFDA91";
static char const* digit_overflow_base17 =      "A7FFDA900";

static char const* max_unsigned_base18 =        "704HE7G3";
static char const* unsigned_overflow_base18 =   "704HE7G4";
static char const* digit_overflow_base18 =      "704HE7G30";

static char const* max_unsigned_base19 =        "4F5AFF65";
static char const* unsigned_overflow_base19 =   "4F5AFF66";
static char const* digit_overflow_base19 =      "4F5AFF650";

static char const* max_unsigned_base20 =        "3723AI4F";
static char const* unsigned_overflow_base20 =   "3723AI4G";
static char const* digit_overflow_base20 =      "3723AI4G0";

static char const* max_unsigned_base21 =        "281D55I3";
static char const* unsigned_overflow_base21 =   "281D55I4";
static char const* digit_overflow_base21 =      "281D55I30";

static char const* max_unsigned_base22 =        "1FJ8B183";
static char const* unsigned_overflow_base22 =   "1FJ8B184";
static char const* digit_overflow_base22 =      "1FJ8B1830";

static char const* max_unsigned_base23 =        "1606K7IB";
static char const* unsigned_overflow_base23 =   "1606K7IC";
static char const* digit_overflow_base23 =      "1606K7IB0";

static char const* max_unsigned_base24 =        "MB994AF";
static char const* unsigned_overflow_base24 =   "MB994AG";
static char const* digit_overflow_base24 =      "MB994AF0";

static char const* max_unsigned_base25 =        "HEK2MGK";
static char const* unsigned_overflow_base25 =   "HEK2MGL";
static char const* digit_overflow_base25 =      "HEK2MGK0";

static char const* max_unsigned_base26 =        "DNCHBNL";
static char const* unsigned_overflow_base26 =   "DNCHBNM";
static char const* digit_overflow_base26 =      "DNCHBNL0";

static char const* max_unsigned_base27 =        "B28JPDL";
static char const* unsigned_overflow_base27 =   "B28JPDM";
static char const* digit_overflow_base27 =      "B28JPDL0";

static char const* max_unsigned_base28 =        "8PFGIH3";
static char const* unsigned_overflow_base28 =   "8PFGIH4";
static char const* digit_overflow_base28 =      "8PFGIH30";

static char const* max_unsigned_base29 =        "76BEIGF";
static char const* unsigned_overflow_base29 =   "76BEIGH";
static char const* digit_overflow_base29 =      "76BEIGF0";

static char const* max_unsigned_base30 =        "5QMCPQF";
static char const* unsigned_overflow_base30 =   "5QMCPQG";
static char const* digit_overflow_base30 =      "5QMCPQF0";

static char const* max_unsigned_base31 =        "4Q0JTO3";
static char const* unsigned_overflow_base31 =   "4Q0JTO4";
static char const* digit_overflow_base31 =      "4Q0JTO30";

static char const* max_unsigned_base32 =        "3VVVVVV";
static char const* unsigned_overflow_base32 =   "3VVVVVW";
static char const* digit_overflow_base32 =      "3VVVVVV0";

static char const* max_unsigned_base33 =        "3AOKQ93";
static char const* unsigned_overflow_base33 =   "3AOKQ94";
static char const* digit_overflow_base33 =      "3AOKQ930";

static char const* max_unsigned_base34 =        "2QHXJLH";
static char const* unsigned_overflow_base34 =   "2QHXJLI";
static char const* digit_overflow_base34 =      "2QHXJLH0";

static char const* max_unsigned_base35 =        "2BR45QA";
static char const* unsigned_overflow_base35 =   "2BR45QB";
static char const* digit_overflow_base35 =      "2BR45QA0";

static char const* max_unsigned_base36 =        "1Z141Z3";
static char const* unsigned_overflow_base36 =   "1Z141Z4";
static char const* digit_overflow_base36 =      "1Z141Z30";

#endif
