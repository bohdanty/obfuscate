#include "rot13.h"

#include <stdexcept>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <sys/time.h>
#include <sys/resource.h>

int main(int argc, char** argv) {
    if (argc != 3) {
        throw std::runtime_error("There should be exactly two parameters");
    }

    auto time = rot13::obfuscate(argv[1], argv[2]);
    std::cout << "Time in the user mode: " << time << std::endl;

    return 0;
}