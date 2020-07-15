#include "rot13.h"

#include <iostream>

namespace rot13 {

extern "C" void obfuscate(char* input, uint length) {
    for (uint i = 0; i < length; i++) {
        char c = input[i];
        if (isalpha(c)) {
            bool lower = islower(c);
            c = (c - (lower ? LOWERCASE_OFFSET : UPPERCASE_OFFSET));
            c = (c + CYPHER_OFFSET) % ALPHABET_SIZE + (lower ? LOWERCASE_OFFSET : UPPERCASE_OFFSET);
        }
        input[i] = c;
    }
}

}