#pragma once

#include <iostream>
#include <algorithm>
#include <iterator>

namespace ret13 {

namespace {
    const uint32_t CYPHER_OFFSET = 13;
    const uint32_t ALPHABET_SIZE = 26;
    const uint32_t UPPERCASE_OFFSET = static_cast<uint32_t>('A');
    const uint32_t LOWERCASE_OFFSET = static_cast<uint32_t>('a');
}

void obfuscate(std::istream& input, std::ostream& output);

}