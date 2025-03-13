package cs5150;

/**
 * An immutable string of characters containing only the upper case letters
 * 'A'-'Z' and the digits '0'-'9'.
 */
class CipherString {
    /** Contents of the string, guaranteed to be valid. */
    private final String validatedText;

    /**
     * Construct a new CipherString from the provided valid text.
     *
     * @param text Contents of the string (must be valid).
     */
    private CipherString(final String text) {
        assert isValid(text);
        validatedText = text;
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
    public CipherString encrypt(final CipherString plaintext) {
        final var k = validatedText;
        final var p = plaintext.validatedText;
        final var len = Math.min(k.length(), p.length());
        final var c = new StringBuilder();
        for (int i = 0; i < len; ++i) {
            c.append(intToChar(mod36(charToInt(p.charAt(i)) +
                                     charToInt(k.charAt(i)))));
        }
        return new CipherString(c.toString());
    }

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
    public CipherString decrypt(final CipherString ciphertext) {
        final var k = validatedText;
        final var c = ciphertext.validatedText;
        final var len = Math.min(k.length(), c.length());
        final var p = new StringBuilder();
        for (int i = 0; i < len; ++i) {
            p.append(intToChar(mod36(charToInt(c.charAt(i)) -
                                charToInt(k.charAt(i)))));
        }
        return new CipherString(p.toString());
    }

    /** Return the characters in this CipherString as a String. */
    @Override
    public String toString() {
        return validatedText;
    }

    @Override
    public boolean equals(Object other) {
        if (other.getClass() != getClass()) {
            return false;
        }
        var cs = (CipherString)other;
        return validatedText.equals(cs.validatedText);
    }

    @Override
    public int hashCode() {
        return validatedText.hashCode();
    }

    /**
     * Return a CipherString containing the provided text, if it is valid.
     *
     * @param text Contents of the string.
     * @return A CipherString containing the provided text.
     * @throws IllegalArgumentException If the provided text is invalid.
     */
    public static CipherString fromString(final String text) {
        if (!isValid(text)) {
            throw new IllegalArgumentException("Invalid CipherString: " + text);
        }
        return new CipherString(text);
    }

    /**
     * Determine whether the characters in a string are allowed in a
     * CipherString.  Allowed characters are the digits '0'-'9' and the upper
     * case letters 'A'-'Z'.
     *
     * @param text The string to validate.
     * @return True if all characters in the provided string are valid, false
     *         otherwise.
     */
    public static boolean isValid(final String text) {
        for (int i = 0; i < text.length(); ++i) {
            final char c = text.charAt(i);
            if (!isValidChar(c)) {
                return false;
            }
        }
        return true;
    }

    /**
     * Determine whether the provided character is allowed in a CipherString.
     * Allowed characters are the digits '0'-'9' and the upper case letters
     * 'A'-'Z'.
     *
     * @param c The character to validate.
     * @return True if the character is valid, false otherwise.
     */
    public static boolean isValidChar(final char c) {
        return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z');
    }

    /**
     * Interpret a valid CipherString character as an integer modulo 35.
     *
     * @param c Character to convert to integer (must be in '0-9A-Z').
     * @return Integer corresponding to character (in 0..35).
     */
    private static int charToInt(final char c) {
        assert isValidChar(c);
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
    private static char intToChar(final int i) {
        assert i >= 0 && i <= 35;
        if (i < 10) {
            return (char)('0' + i);
        } else {
            return (char)('A' + (i - 10));
        }
    }

    /**
     * Return the argument modulo 36, assuming it is no more than one modulus
     * from its canonical value.
     *
     * @param i Number to interpret modulo 36 (must be in -36..71).
     * @return The value of `i` modulo 36 (in 0..35).
     */
    private static int mod36(final int i) {
        assert i >= -36 && i <= 71;
        if (i < 0) {
            return i + 36;
        } else if (i > 35) {
            return i - 36;
        } else {
            return i;
        }
    }
}
