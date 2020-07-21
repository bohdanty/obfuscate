#include <libgen.h>
#include <iostream>

#include "rot13_sapi.sapi.h"
#include "sandboxed_api/util/flag.h"
#include "rot13_sandbox.h"

#include <stdexcept>

// These exist and can be set programmatically
ABSL_DECLARE_FLAG(string, sandbox2_danger_danger_permit_all);
ABSL_DECLARE_FLAG(string, sandbox2_danger_danger_permit_all_and_log);

int main(int argc, char** argv) {
    if (argc != 3) {
        throw std::runtime_error("There should be exactly two parameters");
    }

    Rot13SapiSandbox sandbox;
    sandbox.Init().IgnoreError();

    Rot13Api api(&sandbox);
    sapi::v::ConstCStr in_file(argv[1]);
    sapi::v::ConstCStr out_file(argv[2]);

    std::cout << api.obfuscate(in_file.PtrBefore(), out_file.PtrBefore()).value() << std::endl;

    return 0;
}