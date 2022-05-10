#include <iostream>
#include <cstring>
#include "library/Library.h"

#define MAX_PWD_ATTEMPTS 3
#define MAX_PWD_LEN 128
#define MAX_CMD_LEN 16
#define MAX_STR_LEN 1024

int main() {
    const char *BOOKS_FILENAME = "books.bin";
    const char *USERS_FILENAME = "users.bin";
    const char *ADMIN_PWD = "gosholosho"; // Really making it easy for the ones out there with a decompiler :>

    bool isAdmin = false, isAttemptingAdmin;
    char passwordInput[MAX_PWD_LEN];

    char isAttemptingAdminInput;
    std::cout << "Do you want to login as admin? (y/N): ";
    std::cin >> isAttemptingAdminInput;
    isAttemptingAdmin = isAttemptingAdminInput == 'Y' || isAttemptingAdminInput == 'y';

    for (unsigned int i = 0; i < MAX_PWD_ATTEMPTS && isAttemptingAdmin; i++) {
        std::cout << "Enter administrator password: ";
        std::cin.ignore();
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

    Library library = Library(BOOKS_FILENAME, USERS_FILENAME);

    char command[MAX_CMD_LEN];
    while (std::cout << "|> " && std::cin >> command && std::cin.ignore()) {
        if (!std::strcmp(command, "sort") || !std::strcmp(command, "view")) {
            library.sortBooks();
            library.printBooks();
            continue;
        }

        if (!std::strcmp(command, "find")) {
            char name[MAX_STR_LEN];
            std::cout << "|-> Name: ";
            std::cin.getline(name, MAX_STR_LEN);

            char author[MAX_STR_LEN];
            std::cout << "|-> Author: ";
            std::cin.getline(author, MAX_STR_LEN);

            char ISBN[MAX_STR_LEN];
            std::cout << "|-> ISBN: ";
            std::cin.getline(ISBN, MAX_STR_LEN);

            char descriptionSnippet[MAX_STR_LEN];
            std::cout << "|-> Description snippet: ";
            std::cin.getline(descriptionSnippet, MAX_STR_LEN);

            Book *book = library.findBook(name, author, ISBN, descriptionSnippet);
            if (book == nullptr) {
                std::cerr << "ERR: Book not found!\n";
                continue;
            }
            std::cout << *book;
            continue;
        }

        if (!std::strcmp(command, "add")) {
            if (!isAdmin) {
                std::cerr << "ERR: Admin privileges required!\n";
                continue;
            }

            char name[MAX_STR_LEN];
            std::cout << "|-> Name: ";
            std::cin.getline(name, MAX_STR_LEN);

            char author[MAX_STR_LEN];
            std::cout << "|-> Author: ";
            std::cin.getline(author, MAX_STR_LEN);

            char description[MAX_STR_LEN];
            std::cout << "|-> Description: ";
            std::cin.getline(description, MAX_STR_LEN);

            int rating;
            std::cout << "|-> Rating: ";
            std::cin >> rating;
            std::cin.ignore();

            char ISBN[MAX_STR_LEN];
            std::cout << "|-> ISBN: ";
            std::cin.getline(ISBN, MAX_STR_LEN);

            char filename[MAX_STR_LEN];
            std::cout << "|-> Filename: ";
            std::cin.getline(filename, MAX_STR_LEN);

            library.addBook(Book(name, author, description, rating, ISBN, filename));
            library.updateBooksFile();

            continue;
        }

        if (!std::strcmp(command, "remove")) {
            if (!isAdmin) {
                std::cerr << "ERR: Admin privileges required!\n";
                continue;
            }

            char name[MAX_STR_LEN];
            std::cout << "|-> Name: ";
            std::cin.getline(name, MAX_STR_LEN);

            char author[MAX_STR_LEN];
            std::cout << "|-> Author: ";
            std::cin.getline(author, MAX_STR_LEN);

            char ISBN[MAX_STR_LEN];
            std::cout << "|-> ISBN: ";
            std::cin.getline(ISBN, MAX_STR_LEN);

            if (!library.removeBook(name, author, ISBN)) {
                std::cerr << "ERR: Book not found!\n";
                continue;
            }
            library.updateBooksFile();

            continue;
        }

        if (!std::strcmp(command, "print")) {
            char name[MAX_STR_LEN];
            std::cout << "|-> Name: ";
            std::cin.getline(name, MAX_STR_LEN);

            char author[MAX_STR_LEN];
            std::cout << "|-> Author: ";
            std::cin.getline(author, MAX_STR_LEN);

            char ISBN[MAX_STR_LEN];
            std::cout << "|-> ISBN: ";
            std::cin.getline(ISBN, MAX_STR_LEN);

            unsigned int modeNumber;
            std::cout << "|-> Reading mode (0: whole book, 1: pages, 2: sentences): ";
            std::cin >> modeNumber;
            std::cin.ignore();

            if (modeNumber > 2) {
                std::cerr << "ERR: Invalid mode number!\n";
                continue;
            }

            unsigned int linesCount;
            if ((ReadingMode) modeNumber == PAGES) {
                std::cout << "|-> Lines per page: ";
                std::cin >> linesCount;
                std::cin.ignore();
            }

            Book *book = library.findBook(name, author, ISBN, "");
            if (book == nullptr) {
                std::cerr << "ERR: Book not found!\n";
                continue;
            }

            std::cout << *book << '\n';
            Library::printBookContent(book, (ReadingMode) modeNumber, linesCount);

            continue;
        }

        if (!std::strcmp(command, "exit")) {
            break;
        }
    }

    std::cout << '\n';

    return 0;
}
