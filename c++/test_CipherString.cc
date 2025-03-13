#define BOOST_TEST_MODULE Suite_example
#include <boost/test/included/unit_test.hpp>

#include "CipherString.h"

#include <algorithm>
#include <functional>
#include <stdexcept>
#include <string>

using cs5150::CipherString;

BOOST_AUTO_TEST_SUITE(CipherString_suite)
    BOOST_AUTO_TEST_CASE(testFromStringValid) {
        // Empty string is OK
        BOOST_TEST(CipherString::isValid(""));
        auto const cs1 = CipherString::fromString("");
        BOOST_TEST("" == cs1.validated_text());

        BOOST_TEST(CipherString::isValid("ABC123"));
        auto const cs2 = CipherString::fromString("ABC123");
        BOOST_TEST("ABC123" == cs2.validated_text());
    }

    BOOST_AUTO_TEST_CASE(testFromStringInvalid) {
        // Contains lower case letters
        BOOST_TEST(!CipherString::isValid("abc123"));
        BOOST_CHECK_THROW(CipherString::fromString("abc123"),
                std::runtime_error);

        // Contains a space
        BOOST_TEST(!CipherString::isValid("ABC 123"));
        BOOST_CHECK_THROW(CipherString::fromString("ABC 123"),
                std::runtime_error);

        // Contains Arabic-Indic digits
        BOOST_TEST(!CipherString::isValid("ABC١٢٣"));
        BOOST_CHECK_THROW(CipherString::fromString("ABC١٢٣"),
                std::runtime_error);
    }

    BOOST_AUTO_TEST_CASE(testDecryptEncrypt) {
        auto key = CipherString::fromString("A9Z0M5");
        auto pt = CipherString::fromString("Z0A9N4");
        auto ct = key.encrypt(pt);
        BOOST_TEST(pt == key.decrypt(ct));
    }

    BOOST_AUTO_TEST_CASE(testEquals) {
        auto cs1 = CipherString::fromString("ABC123");
        std::string s2 = "abc123";
        std::transform(s2.begin(), s2.end(), s2.begin(),
                [](unsigned char c) { return std::toupper(c); });
        auto cs2 = CipherString::fromString(s2);
        auto cs3 = CipherString::fromString("321CBA");
        BOOST_TEST(cs1 == cs1);
        BOOST_TEST(cs1 == cs2);
        BOOST_TEST(cs2 == cs1);
        BOOST_TEST(cs1 != cs3);
    }

    BOOST_AUTO_TEST_CASE(testHashCode) {
        auto cs1 = CipherString::fromString("ABC123");
        std::string s2 = "abc123";
        std::transform(s2.begin(), s2.end(), s2.begin(),
                [](unsigned char c) { return std::toupper(c); });
        auto cs2 = CipherString::fromString(s2);
        BOOST_TEST(std::hash<CipherString>{}(cs1) ==
                   std::hash<CipherString>{}(cs2));
    }
BOOST_AUTO_TEST_SUITE_END()
