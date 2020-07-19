#include "rot13.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

namespace rot13 {

suseconds_t get_time_in_user_mode() {
    std::unique_ptr<rusage> usage = std::make_unique<rusage>();
    getrusage(RUSAGE_SELF, usage.get());

    return usage->ru_utime.tv_sec * 1000000 + usage->ru_utime.tv_usec;
}

suseconds_t obfuscate(const char* input_file, const char* output_file) {
    std::ifstream in(input_file);

    if (!in.is_open()) {
        std::stringstream message;
        message << "Can't open file: " << input_file << std::endl;
        throw std::runtime_error(message.str());
    }

    std::ofstream out(output_file);

    char c;

    while (in.get(c)) {
        if (isalpha(c)) {
            bool lower = islower(c);
            c = (c - (lower ? LOWERCASE_OFFSET : UPPERCASE_OFFSET));
            c = (c + CYPHER_OFFSET) % ALPHABET_SIZE + (lower ? LOWERCASE_OFFSET : UPPERCASE_OFFSET);
        }
        out << c;
    }

    in.close();
    out.close();

    return get_time_in_user_mode();
}

}