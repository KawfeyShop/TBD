#include "utils.h"
#include "common_checks.h"

int main() {
    LOG_INFO("Vulnerability checker started.");
    write_to_log_file("Tool initialized");

    // Calling check functions
    check_sticky_keys();
    check_ntlm_usage();
    check_llmnr();

    LOG_INFO("Vulnerability checker finished.");
    write_to_log_file("Tool completed successfully");

    return 0;
}