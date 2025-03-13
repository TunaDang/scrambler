package cs5150;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

class CipherStringTest {
    @Test
    public void testFromStringValid() {
        // Empty string is OK
        assertTrue(CipherString.isValid(""));
        var cs1 = CipherString.fromString("");
        assertEquals("", cs1.toString());

        assertTrue(CipherString.isValid("ABC123"));
        var cs2 = CipherString.fromString("ABC123");
        assertEquals("ABC123", cs2.toString());
    }

    @Test
    public void testFromStringInvalid() {
        // Contains lower case letters
        assertFalse(CipherString.isValid("abc123"));
        assertThrows(IllegalArgumentException.class,
                     () -> CipherString.fromString("abc123"));

        // Contains a space
        assertFalse(CipherString.isValid("ABC 123"));
        assertThrows(IllegalArgumentException.class,
                     () -> CipherString.fromString("ABC 123"));

        // Contains Arabic-Indic digits
        assertFalse(CipherString.isValid("ABC١٢٣"));
        assertThrows(IllegalArgumentException.class,
                     () -> CipherString.fromString("ABC١٢٣"));
    }

    @Test
    public void testDecryptEncrypt() {
        var key = CipherString.fromString("A9Z0M5");
        var pt = CipherString.fromString("Z0A9N4");
        var ct = key.encrypt(pt);
        assertEquals(pt, key.decrypt(ct));
    }

    @Test
    public void testEquals() {
        var cs1 = CipherString.fromString("ABC123");
        var cs2 = CipherString.fromString("abc123".toUpperCase());
        var cs3 = CipherString.fromString("321CBA");
        assertTrue(cs1.equals(cs1));
        assertTrue(cs1.equals(cs2));
        assertTrue(cs2.equals(cs1));
        assertFalse(cs1.equals(cs3));
    }

    @Test
    public void testHashCode() {
        var cs1 = CipherString.fromString("ABC123");
        var cs2 = CipherString.fromString("abc123".toUpperCase());
        assertEquals(cs1.hashCode(), cs2.hashCode());
    }
}
