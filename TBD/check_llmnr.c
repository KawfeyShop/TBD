#include <stdio.h>
#include <windows.h>
#include "common_checks.h"
#include "utils.h"

void check_llmnr() {
    HKEY hKey;
    DWORD dwType = REG_DWORD;
    DWORD value = 0;
    DWORD valueLength = sizeof(value);

    // Path to reg key
    const wchar_t* subKey = L"SOFTWARE\\Policies\\Microsoft\\Windows NT\\DNSClient";

    // Open reg key
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, subKey, 0, KEY_READ, &hKey) != ERROR_SUCCESS) {
        LOG_ERROR("Failed to open the registry key.");
        return;
    }

    // Query the value of the "EnableMulticast" key
    if (RegQueryValueExW(hKey, L"EnableMulticast", NULL, &dwType, (LPBYTE)&value, &valueLength) == ERROR_SUCCESS) {
        printf("[INFO] Multicast Value: %u\n", value);
        if (value == 1) {
            LOG_INFO("Multicast is enabled.");
        } else if (value == 0) {
            LOG_INFO("Multicast is disabled.");
        } else {
            LOG_ERROR("Multicast key isn't 1 or 0.");
        }
    }
    else {
        LOG_ERROR("Failed to query the registry value for multicast.");
    }

    // Close the registry key
    RegCloseKey(hKey);
}
