#include <stdio.h>
#include <windows.h>
#include "common_checks.h"
#include "utils.h"


//returns 0 if sticky keys is disabled, prefered answer, and 1 if enabled
//all other return codes indicate an error
int StickyKeysEnabled() {
    HKEY hKey;
    DWORD dwType = REG_SZ;
    wchar_t value[256];     //Wide charcater type
    DWORD valueLength = sizeof(value);
    LONG lResult;

    // Path to reg key
    const wchar_t* subKey = L"Control Panel\\Accessibility\\StickyKeys";

    // Open reg key
    lResult = RegOpenKeyExW(HKEY_CURRENT_USER, subKey, 0, KEY_READ, &hKey);

    if (lResult != ERROR_SUCCESS) {
        //wprintf(L"Failed to open registry key.\n");
        LOG_ERROR("Failed to open the registry key.");
        return 0x02;
    }

    // Query the value of the "Flags" key
    lResult = RegQueryValueExW(hKey, L"Flags", NULL, &dwType, (LPBYTE)value, &valueLength);

    if (lResult == ERROR_ACCESS_DENIED) {

        LOG_ERROR("Failed to query the registry value.");
        LOG_ERROR("Access Denied.");
        RegCloseKey(hKey);
        return 0x04;
    } else if (lResult == ERROR_FILE_NOT_FOUND) {
        LOG_ERROR("Failed to query the registry value.");
        LOG_ERROR("Registry not found.");
        RegCloseKey(hKey);
        return 0x08;
    } else if (lResult != ERROR_SUCCESS) {
        //wprintf(L"Failed to query the registry value.\n");
        LOG_ERROR("Failed to query the registry value.");
        RegCloseKey(hKey);
        return 0x10;
    }
   
    //wprintf(L"Sticky Keys Flag is: %ls\n", value);

    
    //old code, to be replaced by new return
    // Check if Sticky Keys is enabled (value contains code 510)
    if (wcsstr(value, L"510") != NULL) {
        //wprintf(L"Sticky Keys is enabled.\n");
        LOG_INFO("Sticky Keys is enabled.");
    }
    else if (wcsstr(value, L"506") != NULL) {
        //wprintf(L"Sticky Keys is disabled.\n");
        LOG_INFO("Sticky Keys is disabled.");
    }
    else {
        LOG_ERROR("Sticky Key value isnt 510 or 506.");
    }


    // Close the registry key
    RegCloseKey(hKey);

    //this value only checks if sticky keys is on,
    //not if the window pop up, the vulnerability concern,
    //will open or not. I will need to test how to make that
    //not show, it should be value 0x00000002
    return value | 0x00000001;

}