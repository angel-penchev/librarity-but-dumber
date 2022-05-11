#include <iostream>
#include <cstring>
#include "library/Library.h"

#define MAX_PWD_ATTEMPTS 3
#define MAX_CMD_LEN 32
#define MAX_STR_LEN 1024

int main() {
    const char *BOOKS_FILENAME = "books.bin";
    const char *USERS_FILENAME = "users.bin";

    Library library = Library(BOOKS_FILENAME, USERS_FILENAME);

    char usernameInput[MAX_STR_LEN];
    char passwordInput[MAX_STR_LEN];
    User *user;

    std::cout << "Username: ";
    std::cin.getline(usernameInput, MAX_STR_LEN - 1);

    for (unsigned int i = 0; i < MAX_PWD_ATTEMPTS; i++) {
        std::cout << "Password: ";
        std::cin.getline(passwordInput, MAX_STR_LEN - 1);
        user = library.loginUser(usernameInput, passwordInput);

        if (user != nullptr) {
            break;
        }
    }

    if (user == nullptr) {
        std::cerr << "ERR: Failed to authenticate user!\n";
        return 1;
    }

    char command[MAX_CMD_LEN];
    while (std::cout << "|> " && std::cin.getline(command, MAX_CMD_LEN - 1)) {
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
            if (!user->isAdministrator()) {
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

            double rating;
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

        // Command for adding a user to library
        if (!std::strcmp(command, "add user")) {
            // Validating whether the current user is admin or not
            if (!user->isAdministrator()) {
                std::cerr << "ERR: Admin privileges required!\n";
                continue;
            }

            // User input for user creation
            char username[MAX_STR_LEN];
            std::cout << "|-> Username: ";
            std::cin.getline(username, MAX_STR_LEN);

            char password[MAX_STR_LEN];
            std::cout << "|-> Password: ";
            std::cin.getline(password, MAX_STR_LEN);

            char isAdminChar;
            std::cout << "|-> Is administrator (y/n): ";
            std::cin >> isAdminChar;
            std::cin.ignore();
            bool isAdmin = isAdminChar == 'Y' || isAdminChar == 'y';

            // Create the new user and update the users file
            library.addUser(User(username, password, isAdmin));
            library.updateUsersFile();
        }

        if (!std::strcmp(command, "change password")) {
            char oldPassword[MAX_STR_LEN];
            std::cout << "|-> Old password: ";
            std::cin.getline(oldPassword, MAX_STR_LEN);

            char newPassword[MAX_STR_LEN];
            std::cout << "|-> New password: ";
            std::cin.getline(newPassword, MAX_STR_LEN);

            char newPasswordConfirm[MAX_STR_LEN];
            std::cout << "|-> New password (confirm): ";
            std::cin.getline(newPasswordConfirm, MAX_STR_LEN);

            library.changeUserPassword(user, oldPassword, newPassword, newPasswordConfirm);
        }

        if (!std::strcmp(command, "remove")) {
            if (!user->isAdministrator()) {
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
