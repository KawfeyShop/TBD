#include <stdio.h>
#include <windows.h>
#include "common_checks.h"
#include "utils.h"

void check_ntlm_usage() {
    HKEY hKey;
    DWORD value = 0;
    DWORD valueSize = sizeof(value);

    // Path to the registry key
    const wchar_t* subKey = L"SYSTEM\\CurrentControlSet\\Control\\Lsa";
    const wchar_t* valueName = L"LmCompatibilityLevel";

    // Open the registry key
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, subKey, 0, KEY_READ, &hKey) != ERROR_SUCCESS) {
        fprintf(stderr, "[ERROR] Failed to open registry key: %ls\n", subKey);
        fprintf(stderr, "[ERROR] Or key doesnt exist.");
    }

    // Query the registry value
    if (RegQueryValueExW(hKey, valueName, NULL, NULL, (LPBYTE)&value, &valueSize) == ERROR_SUCCESS) {
        printf("[INFO] LmCompatibilityLevel: %u\n", value);

        // Check if NTLMv1 is allowed
        if (value < 3) {
            printf("[WARNING] NTLMv1 is allowed. Consider setting LmCompatibilityLevel to 3 or higher to disable NTLMv1.\n");
        }
        else {
            printf("[INFO] NTLMv1 is not allowed. The system is configured securely.\n");
        }
    }
    else {
        fprintf(stderr, "[ERROR] Failed to query registry value: %ls\n", valueName);
    }

    // Close the registry key
    RegCloseKey(hKey);
}