"""Unit tests for the cs5150.cipher_string module."""

import unittest

import cs5150.cipher_string
from cs5150.cipher_string import CipherString

class CipherStringTest(unittest.TestCase):
    """Suite of unit tests for CipherString class and related functions."""

    def test_from_string_valid(self):
        # Empty string is OK
        self.assertTrue(cs5150.cipher_string.is_valid(''))
        cs1 = CipherString.from_string('')
        self.assertEqual('', str(cs1))

        self.assertTrue(cs5150.cipher_string.is_valid('ABC123'))
        cs2 = CipherString.from_string('ABC123')
        self.assertEqual('ABC123', str(cs2))

    def test_from_string_invalid(self):
        # Contains lower case letters
        self.assertFalse(cs5150.cipher_string.is_valid('abc123'))
        with self.assertRaises(ValueError):
            CipherString.from_string('abc123')

        # Contains a space
        self.assertFalse(cs5150.cipher_string.is_valid('ABC 123'))
        with self.assertRaises(ValueError):
            CipherString.from_string('ABC 123')

        # Contains Arabic-Indic digits
        self.assertFalse(cs5150.cipher_string.is_valid('ABC١٢٣'))
        with self.assertRaises(ValueError):
            CipherString.from_string('ABC١٢٣')

    def test_decrypt_encrypt(self):
        key = CipherString.from_string('A9Z0M5')
        pt = CipherString.from_string('Z0A9N4')
        ct = key.encrypt(pt)
        self.assertEqual(pt, key.decrypt(ct))

    def test_equals(self):
        cs1 = CipherString.from_string('ABC123')
        cs2 = CipherString.from_string('abc123'.upper())
        cs3 = CipherString.from_string('321CBA')
        self.assertTrue(cs1 == cs1)
        self.assertTrue(cs1 == cs2)
        self.assertTrue(cs2 == cs1)
        self.assertFalse(cs1 == cs3)
        self.assertTrue(cs1 != cs3)

    def test_hash_code(self):
        cs1 = CipherString.from_string('ABC123')
        cs2 = CipherString.from_string('abc123'.upper())
        self.assertEqual(hash(cs1), hash(cs2))

    def test_len(self):
        cs1 = CipherString.from_string('ABC123')
        self.assertEqual(6, len(cs1))

    def test_str(self):
        cs1 = CipherString.from_string('ABC123')
if __name__ == '__main__':
    unittest.main()
