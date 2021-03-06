#pragma once

#include <sys/time.h>
#include <sys/resource.h>

namespace {
    typedef unsigned int uint;
    const uint CYPHER_OFFSET = 13;
    const uint ALPHABET_SIZE = 26;
    const uint UPPERCASE_OFFSET = static_cast<uint>('A');
    const uint LOWERCASE_OFFSET = static_cast<uint>('a');
}

extern "C" long obfuscate(const char* input_file, const char* output_file);