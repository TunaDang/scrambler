#include "CipherString.h"

#include <algorithm>
#include <cassert>
#include <stdexcept>

namespace {
    /**
     * Interpret a valid CipherString character as an integer modulo 35.
     *
     * @param c Character to convert to integer (must be in '0-9A-Z').
     * @return Integer corresponding to character (in 0..35).
     */
    int charToInt(char const c) {
        assert(cs5150::CipherString::isValidChar(c));
        if (c >= '0' && c <= '9') {
            return c - '0';
        } else {
            return 10 + (c - 'A');
        }
    }

    /**
     * Interpret an integer modulo 35 as a CipherString character.
     *
     * @param i Integer to convert to character (must be in 0..35).
     * @return Character corresponding to integer (in '0-9A-Z').
     */
    char intToChar(int const i) {
        assert(i >= 0 && i <= 35);
        if (i < 10) {
            return static_cast<char>('0' + i);
        } else {
            return static_cast<char>('A' + (i - 10));
        }
    }

    /**
     * Return the argument modulo 36, assuming it is no more than one modulus
     * from its canonical value.
     *
     * @param i Number to interpret modulo 36 (must be in -36..71).
     * @return The value of `i` modulo 36 (in 0..35).
     */
    int mod36(int const i) {
        assert(i >= -36 && i <= 71);
        if (i < 0) {
            return i + 36;
        } else if (i > 35) {
            return i - 36;
        } else {
            return i;
        }
    }
}

cs5150::CipherString::CipherString(std::string const & text):
    _validated_text(text) {
    assert(isValid(text));
}

cs5150::CipherString
cs5150::CipherString::encrypt(CipherString const & plaintext) const {
    auto const & k = _validated_text;
    auto const & p = plaintext._validated_text;
    auto const len = std::min(k.size(), p.size());
    std::string c;
    c.reserve(len);
    for (std::size_t i = 0; i < len; ++i) {
        c += intToChar(mod36(charToInt(p[i]) + charToInt(k[i])));
    }
    return CipherString(c);
}

cs5150::CipherString
cs5150::CipherString::decrypt(CipherString const & ciphertext) const {
    auto const & k = _validated_text;
    auto const & c = ciphertext._validated_text;
    auto const len = std::min(k.size(), c.size());
    std::string p;
    p.reserve(len);
    for (std::size_t i = 0; i < len; ++i) {
        p += intToChar(mod36(charToInt(c[i]) - charToInt(k[i])));
    }
    return CipherString(p);
}

cs5150::CipherString
cs5150::CipherString::fromString(std::string const & text) {
    if (!isValid(text)) {
        throw std::runtime_error("Invalid CipherString");
    }
    return CipherString(text);
}

bool cs5150::CipherString::isValid(std::string const & text) {
    for (auto c : text) {
        if (!isValidChar(c)) {
            return false;
        }
    }
    return true;
}

bool cs5150::CipherString::isValidChar(char const c) {
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z');
}

namespace cs5150 {
    std::ostream & operator<<(std::ostream & os, CipherString const & cs) {
        return os << cs._validated_text;
    }
}

namespace std {
    size_t hash<cs5150::CipherString>::operator()(
            cs5150::CipherString const & cs) const {
        return hash<string>{}(cs._validated_text);
    }
}
