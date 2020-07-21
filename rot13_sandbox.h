#pragma once

#include "rot13_sapi.sapi.h"
#include "sandboxed_api/sandbox2/policy.h"
#include "sandboxed_api/sandbox2/policybuilder.h"
#include "sandboxed_api/util/flag.h"

#include <memory>
#include <syscall.h>
#include <libgen.h>

class Rot13SapiSandbox : public Rot13Sandbox {
public:
    std::unique_ptr<sandbox2::Policy> ModifyPolicy(
        sandbox2::PolicyBuilder*) override {
            return sandbox2::PolicyBuilder()
                .DisableNamespaces()
                .AllowStaticStartup()
                .AllowOpen()
                .AllowRead()
                .AllowWrite()
                .AllowSystemMalloc()
                .AllowExit()
                .AllowSyscalls({
                  __NR_futex,  // Google logging and Abseil use this
                  __NR_close,
                  __NR_getrusage,
                })
                .BuildOrDie();
    }
};