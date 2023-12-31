#include "Injector.h"
#include "Seh.h"
#include "StringWrap.h"
#include "argh.h"
#include "StringUtil.h"
#include <fcntl.h>

// Windows API
#include <Windows.h>
#include <tchar.h>
#include <TlHelp32.h>
#include <Shlwapi.h>

// C++ Standard Library
#include <iostream>
#include <string>
#include <locale>
#include <io.h>

// Return values
#define RESULT_SUCCESS          0
#define RESULT_GENERAL_ERROR    2
#define RESULT_SEH_ERROR        3
#define RESULT_UNKNOWN_ERROR    4

// Function to set console text color
void SetConsoleColor(WORD color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Function to get the module path
std::tstring GetModulePath()
{
    TCHAR modulePath[MAX_PATH];
    GetModuleFileName(NULL, modulePath, MAX_PATH);
    std::tstring fullPath(modulePath);
    size_t lastBackslashPos = fullPath.find_last_of(_T("\\"));
    if (lastBackslashPos != std::tstring::npos) {
        fullPath = fullPath.substr(0, lastBackslashPos + 1);
    }
    fullPath += _T("Rumbleverse.dll");
    return fullPath;
}

// Function to get the module path
std::tstring GetModulePath2()
{
    TCHAR modulePath[MAX_PATH];
    GetModuleFileName(NULL, modulePath, MAX_PATH);
    std::tstring fullPath(modulePath);
    size_t lastBackslashPos = fullPath.find_last_of(_T("\\"));
    if (lastBackslashPos != std::tstring::npos) {
        fullPath = fullPath.substr(0, lastBackslashPos + 1);
    }
    fullPath += _T("UniversalUE4Unlocker.dll");
    return fullPath;
}

DWORD GetProcessIdByProcessName(const std::wstring& processName)
{
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
    {
        return 0;
    }

    DWORD processId = 0;

    if (Process32First(hSnapshot, &pe32))
    {
        do
        {
            if (_wcsicmp(pe32.szExeFile, processName.c_str()) == 0)
            {
                processId = pe32.th32ProcessID;
                break;
            }
        } while (Process32Next(hSnapshot, &pe32));
    }

    CloseHandle(hSnapshot);
    return processId;
}

int main()
{
    try
    {
        // Get the current console window size
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(consoleHandle, &csbi);

        // Define new width and height
        SHORT newWidth = csbi.srWindow.Right + 10;  // Increase width by 5 columns
        SHORT newHeight = csbi.srWindow.Bottom + 17; // Increase height by 5 rows

        // Set the new console screen buffer size
        COORD bufferSize = { newWidth, newHeight };
        SetConsoleScreenBufferSize(consoleHandle, bufferSize);

        // Set the new console window size
        SMALL_RECT windowSize = { 0, 0, newWidth - 1, newHeight - 1 };
        SetConsoleWindowInfo(consoleHandle, TRUE, &windowSize);
        
        SehGuard Guard;

        // Injector version number
        const std::tstring VerNum(_T("ProjKO V1"));

        // Version and copyright output
        SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
#ifdef _WIN64
        std::tcout << _T("--Rumble Injector x64 [Version: ") << VerNum << _T("]--") << std::endl;
#else
        std::tcout << _T("--Rumble Injector x86 [Version: ") << VerNum << _T("]--") << std::endl;
#endif
        SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN);
        _setmode(_fileno(stdout), _O_U16TEXT);
        std::wcout << LR"(
            ██████████                          ██████████    
            ██        ████                  ████        ██    
            ██            ██  ██████████  ██            ██    
            ██              ██    ▒▒    ██              ██    
            ██              ██    ▒▒    ██              ██    
            ██              ██  ▒▒▒▒▒▒  ██              ██    
          ██  ██              ▒▒      ▒▒              ██  ██  
        ██      ██          ▒▒          ▒▒          ██      ██
        ██                  ▒▒N  0  v  a▒▒        ██        ██
        ██                  ▒▒W  0  1  f▒▒                  ██
        ██                    ▒▒      ▒▒                    ██                                        
        ██      ▒▒              ▒▒▒▒▒▒              ▒▒      ██
        ██      ▒▒▒▒████▒▒        ▒▒        ▒▒████▒▒▒▒      ██
        ██      ▒▒▒▒██████▒▒      ▒▒      ▒▒██████▒▒▒▒      ██
          ██    ▒▒▒▒████████▒▒    ▒▒    ▒▒████████▒▒▒▒    ██  
            ██    ▒▒▒▒██████  ▒▒  ▒▒  ▒▒  ██████▒▒▒▒    ██    
            ██      ▒▒▒▒████  ▒▒  ▒▒  ▒▒  ████▒▒▒▒      ██    
              ██      ▒▒▒▒▒▒      ▒▒      ▒▒▒▒▒▒      ██      
                ██████    ▒▒      ▒▒      ▒▒    ██████        
                    ██            ▒▒            ██            
                      ██          ▒▒          ██              
                      ██          ▒▒          ██              
                      ██      ██████████      ██              
                      ██    ██████████████    ██              
                        ██    ██████████    ██                
                          ██              ██                  
                            ██          ██                    
                              ██████████                      
    )" << std::endl;
        _setmode(_fileno(stdout), _O_TEXT);
        std::tcout << _T("\n\nOriginal Injector Developer:--Copyright (c) 2009 Cypher, 2012-2023 Nefarius. All rights reserved.-- \n\nMy Contributions:***Modified for instant detection of the rumbleverse process & seamless injection of the Rumbleverse DLL.*** \n\n--Credit goes to the original copyright holders.-- \n\nShoutout to systemdev who generated the SDK + everyone else because yall are awesome <3 - N0vaW01f") << std::endl << std::endl;
        // Find and inject via process name
        DWORD procId = GetProcessIdByProcessName(_T("RumbleverseClient-Win64-Shipping.exe"));

        if (procId != 0)
        {
            // Print PID
            SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            std::tcout << "--Found Rumbleverse process with ID: " << procId << "--" << std::endl;

            // Get the module path
 // Get the module path for the first DLL (Rumbleverse.dll)
            std::tstring modulePath1 = GetModulePath();

            // Check if the module path exists
            if (GetFileAttributes(modulePath1.c_str()) != INVALID_FILE_ATTRIBUTES)
            {
                // Module exists, use the custom path
                std::tcout << "DLL located at: " << modulePath1 << std::endl;
            }
            else
            {
                // Module doesn't exist, use the default path
                std::tcout << "Module (Rumbleverse.dll) not found in the same directory as the injector. We need this file! using last known defaults.  " << std::endl;
                modulePath1 = _T("Rumbleverse.dll");
            }

            // Get privileges required to perform the injection
            std::cout << "Initializing injection for Rumbleverse.dll..." << std::endl;
            Sleep(9000); // Wait for 9 seconds

            // Inject the first module
            Injector::Get()->GetSeDebugPrivilege();
            Injector::Get()->InjectLib(procId, modulePath1);

            // If we get to this point then no exceptions have been thrown, so we assume success.
            SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
            std::tcout << "Successfully injected module (Rumbleverse.dll) into Rumbleverse!" << std::endl;
            Sleep(3000);

            // Get the module path for the second DLL (UniversalUE4Unlocker.dll)
            std::tstring modulePath2 = GetModulePath2();

            // Check if the module path exists
            if (GetFileAttributes(modulePath2.c_str()) != INVALID_FILE_ATTRIBUTES)
            {
                // Module exists, use the custom path
                std::tcout << "DLL located at: " << modulePath2 << std::endl;
            }
            else
            {
                // Module doesn't exist, use the default path
                std::tcout << "Module (UniversalUE4Unlocker.dll) not found in the same directory as the injector. This file isn't super important but it will allow you to use console commands among other things; using last known defaults.  " << std::endl;
                modulePath2 = _T("UniversalUE4Unlocker.dll");
            }

            // Get privileges required to perform the injection
            std::cout << "Initializing injection for UniversalUE4Unlocker.dll..." << std::endl;
            Sleep(9000); // Wait for 9 seconds

            // Inject the second module
            Injector::Get()->GetSeDebugPrivilege();
            Injector::Get()->InjectLib(procId, modulePath2);

            // If we get to this point then no exceptions have been thrown, so we assume success.
            SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
            std::tcout << "Successfully injected module (UniversalUE4Unlocker.dll) into Rumbleverse!" << std::endl;
            Sleep(3000);

        }
        else
        {
            // Process not found, terminate the application
            SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
            std::tcout << "Process is not active. Please execute the rumbleverse process. \nPlease allow the game to load fully onto the login screen before opening." << std::endl;
            Sleep(5000);
            return RESULT_SUCCESS;
        }
    }
    catch (const std::exception& e)
    {
        SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        std::string tempError(e.what());
        std::tstring error(tempError.begin(), tempError.end());
        std::tcerr << "General Error:" << std::endl
            << error << std::endl;
        Sleep(3000);
        return RESULT_GENERAL_ERROR;
    }
    catch (const SehException& e)
    {
        SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        std::tcerr << "SEH Error:" << std::endl
            << e.GetCode() << std::endl;
        Sleep(3000);
        return RESULT_SEH_ERROR;
    }
    catch (...)
    {
        SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        std::tcerr << "Unknown error!" << std::endl;
        Sleep(3000);
        return RESULT_UNKNOWN_ERROR;
    }

    return RESULT_SUCCESS;
}