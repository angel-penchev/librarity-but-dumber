#include <iostream>
#include <cstring>
#include <fstream>
#include "src/library/Library.h"

#define MAX_PWD_ATTEMPTS 3
#define MAX_PWD_LEN 128
#define MAX_CMD_LEN 16
#define BOOKS_FILE "books.bin"
#define USERS_FILE "users.bin"

const char *ADMIN_PWD = "gosholosho"; // Really making it easy for the ones out there with a decompiler :>

int main() {
    bool isAdmin = false, isAttemptingAdmin;
    char passwordInput[MAX_PWD_LEN];

    char isAttemptingAdminInput;
    std::cout << "Do you want to login as admin? (y/N): ";
    std::cin >> isAttemptingAdminInput;
    isAttemptingAdmin = isAttemptingAdminInput == 'Y' || isAttemptingAdminInput == 'y';

    std::cin.ignore();
    for (unsigned int i = 0; i < MAX_PWD_ATTEMPTS && isAttemptingAdmin; i++) {
        std::cout << "Enter administrator password: ";
        std::cin.getline(passwordInput, MAX_PWD_LEN - 1);
        if (!std::strcmp(passwordInput, ADMIN_PWD)) {
            isAdmin = true;
            break;
        }
    }

    if (isAttemptingAdmin && !isAdmin) {
        std::cerr << "Failed to login as admin!\n";
        return 1;
    }

    std::ifstream booksFile(BOOKS_FILE, std::ios::binary);
    if (!booksFile){
        std::cerr << "Couldn't open books database for reading!" << std::endl;
        return 2;
    }

    std::ifstream usersFile(USERS_FILE, std::ios::binary);
    if (!usersFile){
        std::cerr << "Couldn't open users database for reading!" << std::endl;
        return 3;
    }

    Library library = Library(booksFile, usersFile);

    booksFile.close();
    usersFile.close();

    char command[MAX_CMD_LEN];
    while (std::cout << "> " && std::cin >> command) {
        if (!std::strcmp(command, "sort")) {
            library.sortBooks();
            library.printBooks();
            continue;
        }

        if (!std::strcmp(command, "find")) {
            Book *book = library.findBook("gosho", "losho", "00-00", "never gonna");
            if (book == nullptr) {
                std::cerr << "ERR: Book not found!\n";
                continue;
            }
            std::cout << book;
            continue;
        }

        if (!std::strcmp(command, "add")) {
            if (!isAdmin) {
                std::cerr << "ERR: Admin privileges required!\n";
                continue;
            }

            library.addBook(Book());

            continue;
        }

        if (!std::strcmp(command, "remove")) {
            if (!isAdmin) {
                std::cerr << "ERR: Admin privileges required!\n";
                continue;
            }

            library.removeBook("gosho", "losho", "00-00", "never gonna");

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
