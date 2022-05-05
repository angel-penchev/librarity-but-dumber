#include <iostream>
#include <cstring>

#define ADMIN_PWD "gosholosho" // Really making it easy for the ones out there with a decompiler :>
#define MAX_PWD_ATTEMPTS 3
#define MAX_PWD_LEN 128
#define MAX_CMD_LEN 16

int main() {
    bool isAdmin = false, isAttemptingAdmin;
    char passwordInput[MAX_PWD_LEN];

    char isAttemptingAdminInput;
    std::cout << "Do you want to login as admin? (y/N): ";
    std::cin >> isAttemptingAdminInput;
    isAttemptingAdmin = isAttemptingAdminInput == 'Y' || isAttemptingAdminInput == 'y';

    for (unsigned int i = 0; i < MAX_PWD_ATTEMPTS && isAttemptingAdmin; i++) {
        std::cout << "Enter administrator password: ";
        std::cin.getline(passwordInput, MAX_PWD_LEN - 1);
        if (std::strcmp(passwordInput, ADMIN_PWD) == 0) {
            isAdmin = true;
            continue;
        }
    }

    if (isAttemptingAdmin && !isAdmin) {
        std::cerr << "Failed to login as admin!\n";
        return 1;
    }

    char command[MAX_CMD_LEN];
    while (std::cout << "> " && std::cin >> command) {
        if (!std::strcmp(command, "sort")) {
            continue;
        }

        if (!std::strcmp(command, "find")) {
            continue;
        }

        if (!std::strcmp(command, "add")) {
            if (!isAdmin) {
                std::cerr << "ERR: Admin privileges required!\n";
                continue;
            }

            continue;
        }

        if (!std::strcmp(command, "remove")) {
            if (!isAdmin) {
                std::cerr << "ERR: Admin privileges required!\n";
                continue;
            }

            continue;
        }

        if (!std::strcmp(command, "print")) {
            continue;
        }

        if (!std::strcmp(command, "exit")) {
            break;
        }
    }

    return 0;
}
