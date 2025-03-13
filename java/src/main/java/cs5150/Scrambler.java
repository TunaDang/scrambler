package cs5150;

/** Application that scrambles argument using a hard-coded key. */
public class Scrambler {
    /**
     * Scramble the first argument string.
     *
     * @param args Program arguments (must have length 1).
     */
    public static void main(final String[] args) {
        if (args.length != 1) {
            System.err.println("Invalid number of arguments (" + args.length +
                               " != 1)");
            System.err.println("Usage: java cs5150.Scrambler <plaintext>");
            System.exit(1);
        }
        final var key = CipherString.fromString("cdm89".toUpperCase());

        try {
            final var plaintext = CipherString.fromString(
                    args[0].toUpperCase());
            System.out.println(key.encrypt(plaintext));
        } catch (IllegalArgumentException e) {
            System.err.println("Invalid plaintext - must be alphanumeric");
            System.exit(1);
        }
    }
}
