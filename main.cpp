#include "rot13.h"

#include <stdexcept>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <sys/time.h>
#include <sys/resource.h>

std::string read_from_input(std::istream& input) {
    std::string result;
    char c;

    while (input.get(c)) {
        result.push_back(c);
    }

    return result;
}

void process_data(std::istream& input, std::ostream& output) {
    std::string data = read_from_input(input);
    
    if (data.length() > 0) {
        rot13::obfuscate(&data[0], data.length());
    }

    for (char c : data) {
        output << c;
    }
}

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

    process_data(input, output);

    input.close();
    output.close();

    std::cout << "Time in the user mode: " << get_time_in_user_mode() << std::endl;

    return 0;
}