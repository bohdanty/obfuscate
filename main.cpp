#include "ret13.h"

#include <stdexcept>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <sys/time.h>
#include <sys/resource.h>

suseconds_t get_time_in_user_mode() {
    std::unique_ptr<rusage> usage = std::make_unique<rusage>();
    getrusage(RUSAGE_SELF, usage.get());

    return usage->ru_utime.tv_usec;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        throw std::runtime_error("There should be exactly two parameters");
    }

    std::ifstream input(argv[1]);
    std::ofstream output(argv[2]);

    if (!input.is_open()) {
        std::stringstream message;
        message << "Can't open file: " << argv[1] << std::endl;
        throw std::runtime_error(message.str());
    }

    ret13::obfuscate(input, output);

    input.close();
    output.close();

    std::cout << "Time in the user mode: " << get_time_in_user_mode() << std::endl;

    return 0;
}