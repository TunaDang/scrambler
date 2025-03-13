#pragma once

#include <cstdlib>
#include <functional>
#include <ostream>
#include <string>

namespace cs5150 {
    class CipherString;

    std::ostream & operator<<(std::ostream & os, CipherString const & cs);
}

namespace std {
    template<>
    struct hash<cs5150::CipherString> {
        size_t operator()(cs5150::CipherString const & cs) const;
    };
}

/**
 * An immutable string of characters containing only the upper case letters
 * 'A'-'Z' and the digits '0'-'9'.
 */
class cs5150::CipherString {
  public:
    /** Return the characters in this CipherString as a String. */
    std::string const & validated_text() const {
        return _validated_text;
    }

    /**
     * Encrypt the provided text using this string as a key.
     * Each character of both strings is interpreted as a number in the range
     * 0..35 ('0'-'9' map to themselves and 'A'-'Z' map to 10..35).  Each
     * character of the plaintext is shifted by the corresponding character of
     * the key, modulo 35.  Only characters at positions less than the length of
     * the key are considered.
     *
     * @param plaintext Text to be encrypted.
     * @return Ciphertext after encrypting plaintext using this CipherString as
     *         the key.
     */
    CipherString encrypt(CipherString const & plaintext) const;

    /**
     * Decrypt the provided text using this string as a key.
     * Each character of both strings is interpreted as a number in the range
     * 0..35 ('0'-'9' map to themselves and 'A'-'Z' map to 10..35).  Each
     * character of the plaintext is shifted by the negation of the
     * corresponding character of the key, modulo 35.  Only characters at
     * positions less than the length of the key are considered.
     *
     * @param ciphertext Text to be decrypted.
     * @return Plaintext after decrypting ciphertext using this CipherString as
     *         the key.
     */
    CipherString decrypt(CipherString const & ciphertext) const;

    /**
     * Return a CipherString containing the provided text, if it is valid.
     *
     * @param text Contents of the string.
     * @return A CipherString containing the provided text.
     * @throws std::runtime_error If the provided text is invalid.
     */
    static CipherString fromString(std::string const & text);

    /**
     * Determine whether the characters in a string are allowed in a
     * CipherString.  Allowed characters are the digits '0'-'9' and the upper
     * case letters 'A'-'Z'.
     *
     * @param text The string to validate.
     * @return True if all characters in the provided string are valid, false
     *         otherwise.
     */
    static bool isValid(std::string const & text);

    /**
     * Determine whether the provided character is allowed in a CipherString.
     * Allowed characters are the digits '0'-'9' and the upper case letters
     * 'A'-'Z'.
     *
     * @param c The character to validate.
     * @return True if the character is valid, false otherwise.
     */
    static bool isValidChar(char c);

    bool operator==(CipherString const & other) const {
        return _validated_text == other._validated_text;
    }

    bool operator!=(CipherString const & other) const {
        return !(*this == other);
    }

  private:
    /** Contents of the string, guaranteed to be valid. */
    std::string const _validated_text;

    /**
     * Construct a new CipherString from the provided valid text.
     *
     * @param text Contents of the string (must be valid).
     */
    CipherString(std::string const & text);

    friend std::ostream & operator<<(std::ostream &, CipherString const &);
    friend std::hash<CipherString>;
};
