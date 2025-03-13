"""Handle alphanumeric strings suitable for encryption in Z_36."""

from dataclasses import dataclass

#@dataclass(frozen=True, kw_only=True)  # Requires Python 3.10
@dataclass(frozen=True)
class CipherString:
    """
    An immutable string of characters containing only the upper case letters
    'A'-'Z' and the digits '0'-'9'.
    """

    validated_text: str
    """Contents of the string, guaranteed to be valid."""

    def encrypt(self, plaintext: 'CipherString') -> 'CipherString':
        """
        Encrypt the provided text using this string as a key.
        Each character of both strings is interpreted as a number in the range
        0..35 ('0'-'9' map to themselves and 'A'-'Z' map to 10..35).  Each
        character of the plaintext is shifted by the corresponding character of
        the key, modulo 35.  Only characters at positions less than the length
        of the key are considered.

        :param plaintext: Text to be encrypted.
        :return: Ciphertext after encrypting plaintext using this CipherString
                 as the key.
        """
        k = self.validated_text
        p = plaintext.validated_text
        min_len = min(len(k), len(p))
        c = ''
        for i in range(min_len):
            c += int_to_char(mod36(char_to_int(p[i]) +
                                   char_to_int(k[i])))
        return CipherString(validated_text=c)

    def decrypt(self, ciphertext: 'CipherString') -> 'CipherString':
        """
        Decrypt the provided text using this string as a key.
        Each character of both strings is interpreted as a number in the range
        0..35 ('0'-'9' map to themselves and 'A'-'Z' map to 10..35).  Each
        character of the plaintext is shifted by the negation of the
        corresponding character of the key, modulo 35.  Only characters at
        positions less than the length of the key are considered.

        :param ciphertext: Text to be decrypted.
        :return: Plaintext after decrypting ciphertext using this CipherString
                 as the key.
        """
        k = self.validated_text
        c = ciphertext.validated_text
        min_len = min(len(k), len(c))
        p = ''
        for i in range(min_len):
            p += int_to_char(mod36(char_to_int(c[i]) -
                                   char_to_int(k[i])))
        return CipherString(validated_text=p)

    def __str__(self) -> str:
        """Return the characters in this CipherString as a string."""
        return self.validated_text

    def __len__(self) -> int:
        """Return the number of characters in this CipherString."""
        return len(self.validated_text)

    def from_string(text: str) -> 'CipherString':
        """
        Return a CipherString containing the provided text, if it is valid.
        Otherwise, raise a ValueError.

        :param text: Contents of the string.
        :return: A CipherString containing the provided text.
        :raises ValueError: If the provided text is invalid.
        """
        if not is_valid(text):
            raise ValueError(f'Invalid CipherString: {text}')
        return CipherString(validated_text=text)

def is_valid(text: str) -> bool:
    """
    Determine whether the characters in a string are allowed in a
    CipherString.  Allowed characters are the digits '0'-'9' and the upper
    case letters 'A'-'Z'.

    :param text: The string to validate.
    :return: True if all characters in the provided string are valid, false
             otherwise.
    """
    for c in text:
        if not is_valid_char(c):
            return False
    return True

def is_valid_char(c: chr) -> bool:
    """
    Determine whether the provided character is allowed in a CipherString.
    Allowed characters are the digits '0'-'9' and the upper case letters
    'A'-'Z'.

    :param c: The character to validate.
    :return: True if the character is valid, false otherwise.
    """
    return ('0' <= c <= '9') or ('A' <= c <= 'Z')

def char_to_int(c: chr) -> bool:
    """
    Interpret a valid CipherString character as an integer modulo 35.

    :param c: Character to convert to integer (must be in '0-9A-Z').
    :return: Integer corresponding to character (in 0..35).
    """
    assert is_valid_char(c)
    if '0' <= c <= '9':
        return ord(c) - ord('0')
    return 10 + (ord(c) - ord('A'))

def int_to_char(i: int) -> chr:
    """
    Interpret an integer modulo 35 as a CipherString character.

    :param i: Integer to convert to character (must be in 0..35).
    :return: Character corresponding to integer (in '0-9A-Z').
    """
    assert 0 <= i <= 35
    if i < 10:
        return chr(ord('0') + i)
    return chr(ord('A') + (i - 10))

def mod36(i: int) -> int:
    """
    Return the argument modulo 36, assuming it is no more than one modulus
    from its canonical value.

    :param i: Number to interpret modulo 36 (must be in -36..71).
    :return: The value of `i` modulo 36 (in 0..35).
    """
    assert -36 <= i <= 71
    if i < 0:
        return i + 36
    if i > 35:
        return i - 36
    return i
