#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

#include "CipherString.h"

using cs5150::CipherString;

/**
 * Scramble the first argument string.
 *
 * @param argc Number of program arguments.
 * @param argv Pointer to first program argument.
 */
int main(int argc, char const * const * const argv) {
    if (argc != 2) {
        std::cerr << "Invalid number of arguments (" << (argc - 1) <<
                     " != 1)" << std::endl;
        if (argc > 0) {
            std::cerr << "Usage: " << argv[0] << " <plaintext>" << std::endl;
        }
        return EXIT_FAILURE;
    }
    std::string key_string = "cdm89";
    std::transform(key_string.begin(), key_string.end(), key_string.begin(),
            [](unsigned char c) { return std::toupper(c); });
    auto const key = CipherString::fromString(key_string);

    try {
        std::string p_string(argv[1]);
        std::transform(p_string.begin(), p_string.end(), p_string.begin(),
                [](unsigned char c) { return std::toupper(c); });
        auto const plaintext = CipherString::fromString(p_string);
        std::cout << key.encrypt(plaintext) << std::endl;
    } catch (std::runtime_error const & e) {
        std::cerr << "Invalid plaintext - must be alphanumeric" << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
