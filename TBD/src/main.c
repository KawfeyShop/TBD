#include "utils.h"
#include "common_checks.h"

int main() {
    LOG_INFO("Vulnerability checker started.");
    write_to_log_file("Tool initialized");

    // Calling check functions
    if (StickyKeysEnabled()) {
        printf("sticky key on");
    }
    else {
        printf("sticky keys off");
    }
    check_ntlm_usage();

    LOG_INFO("Vulnerability checker finished.");
    write_to_log_file("Tool completed successfully");

    return 0;
}