#include "ret13.h"

namespace ret13 {

void obfuscate(std::istream& input, std::ostream& output) {
    std::transform(std::istreambuf_iterator<char>(input),
            std::istreambuf_iterator<char>(),
            std::ostreambuf_iterator<char>(output),
            [](char c) -> char { 
                if (isalpha(c)) {
                    bool lower = islower(c);
                    c = (c - (lower ? LOWERCASE_OFFSET : UPPERCASE_OFFSET));
                    c = (c + CYPHER_OFFSET) % ALPHABET_SIZE + (lower ? LOWERCASE_OFFSET : UPPERCASE_OFFSET);
                }

                return c;
            }
    );
}

}