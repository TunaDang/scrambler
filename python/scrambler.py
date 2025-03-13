"""Scramble the first argument string."""

import sys
from cs5150.cipher_string import CipherString

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print(f'Invalid number of arguments ({len(sys.argv) - 1} != 1)',
              file=sys.stderr)
        raise SystemExit(f'Usage: {sys.argv[0]} <plaintext>')
    try:
        p = CipherString.from_string(sys.argv[1].upper())
        k = CipherString.from_string('cdm89'.upper())
        print(k.encrypt(p))
    except ValueError:
        raise SystemExit('Invalid plaintext - must be alphanumeric')
