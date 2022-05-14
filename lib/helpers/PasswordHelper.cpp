//
// Created by apenchev on 5/13/2022.
//

#include "../../include/helpers/PasswordHelper.h"

#ifdef _WIN32

#include <windows.h>

void PasswordHelper::enableInputEcho(bool on) {
    // Get current console mode
    DWORD mode;
    HANDLE hConIn = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hConIn, &mode);

    // Change mode to enable/Disable echo for input characters and apply it
    mode = on
           ? (mode | ENABLE_ECHO_INPUT)
           : (mode & ~(ENABLE_ECHO_INPUT));
    SetConsoleMode(hConIn, mode);
}

#else

#include <termios.h>
#include <unistd.h>

void PasswordHelper::enableInputEcho(bool on) {
    // Get current terminal settings
    struct termios settings{};
    tcgetattr(STDIN_FILENO, &settings);

    // Enable/Disable echo for input characters and apply immediately
    settings.c_lflag = on
                       ? (settings.c_lflag | ECHO)
                       : (settings.c_lflag & ~(ECHO));
    tcsetattr(STDIN_FILENO, TCSANOW, &settings);
}

#endif

void PasswordHelper::inputPassword(char *passwordBuffer, unsigned int length, bool printNewLine) {
    // Disable terminal character printing
    enableInputEcho(false);

    // Get password input
    std::cin.getline(passwordBuffer, length);

    // Enable terminal character printing
    enableInputEcho(true);

    // Print a new line after input
    if (printNewLine) {
        std::cout << "\n";
    }
}