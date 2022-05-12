//
// Created by apenchev on 5/12/2022.
//

#include "LibrarityButDumber.h"

int LibrarityButDumber::run() {
    // Set binary file locations and initialize a library object
    const char *BOOKS_FILENAME = "books.bin";
    const char *USERS_FILENAME = "users.bin";

    Library library = Library(BOOKS_FILENAME, USERS_FILENAME);

    // Attempt to login user
    char usernameInput[MAX_STR_LEN];
    char passwordInput[MAX_STR_LEN];
    User *user;

    // Getting user username input
    std::cout << "Username: ";
    std::cin.getline(usernameInput, MAX_STR_LEN - 1);

    for (unsigned int i = 0; i < MAX_PWD_ATTEMPTS; i++) {
        // Getting user password input
        std::cout << "Password: ";
        std::cin.getline(passwordInput, MAX_STR_LEN - 1);

        // Attempt logging in with the submitted credentials
        user = library.loginUser(usernameInput, passwordInput);

        // Break out of the password loop if the login is successful
        if (user != nullptr) {
            break;
        }
    }

    // Authentication failed if the user is null after 3 password inputs
    if (user == nullptr) {
        std::cerr << "ERR: Failed to authenticate user!\n";
        return 1;
    }

    char command[MAX_CMD_LEN];
    while (std::cout << "|> " && std::cin.getline(command, MAX_CMD_LEN - 1)) {
        // Command for adding a user to the library
        if (!std::strcmp(command, "add user")) {
            // Validating whether the current user is administrator or not
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

        // Command for changing your own password
        if (!std::strcmp(command, "change password")) {
            // User input for password change
            char oldPassword[MAX_STR_LEN];
            std::cout << "|-> Old password: ";
            std::cin.getline(oldPassword, MAX_STR_LEN);

            char newPassword[MAX_STR_LEN];
            std::cout << "|-> New password: ";
            std::cin.getline(newPassword, MAX_STR_LEN);

            char newPasswordConfirm[MAX_STR_LEN];
            std::cout << "|-> New password (confirm): ";
            std::cin.getline(newPasswordConfirm, MAX_STR_LEN);

            // Changing the user password
            library.changeUserPassword(user, oldPassword, newPassword, newPasswordConfirm);
        }

        // Command for outputting all books in the library
        if (!std::strcmp(command, "view")) {
            library.printBooks();
            continue;
        }

        // Command for sorting and outputting all books in the library
        if (!std::strcmp(command, "sort")) {
            library.sortBooks();
            library.printBooks();
            continue;
        }

        // Command for adding a book to the library
        if (!std::strcmp(command, "add") || !std::strcmp(command, "add book")) {
            // Validating whether the current user is administrator or not
            if (!user->isAdministrator()) {
                std::cerr << "ERR: Admin privileges required!\n";
                continue;
            }

            // User input for book information
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

            // Create the new book and update the books file
            library.addBook(Book(name, author, description, rating, ISBN, filename));
            library.updateBooksFile();

            continue;
        }

        // Command for removing a book from the library
        if (!std::strcmp(command, "remove")) {
            // Validating whether the current user is administrator or not
            if (!user->isAdministrator()) {
                std::cerr << "ERR: Admin privileges required!\n";
                continue;
            }

            // Search criteria for the book to be removed
            char name[MAX_STR_LEN];
            std::cout << "|-> Name: ";
            std::cin.getline(name, MAX_STR_LEN);

            char author[MAX_STR_LEN];
            std::cout << "|-> Author: ";
            std::cin.getline(author, MAX_STR_LEN);

            char ISBN[MAX_STR_LEN];
            std::cout << "|-> ISBN: ";
            std::cin.getline(ISBN, MAX_STR_LEN);

            // Search for the book and remove it if it's found
            if (!library.removeBook(name, author, ISBN)) {
                std::cerr << "ERR: Book not found!\n";
                continue;
            }

            // Update the books file if the book is removed
            library.updateBooksFile();

            continue;
        }

        // Command for searching for a book and printing its information
        if (!std::strcmp(command, "find") || !std::strcmp(command, "search")) {
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

        if (!std::strcmp(command, "print")) {
            // User input criteria for the book to print
            char name[MAX_STR_LEN];
            std::cout << "|-> Name: ";
            std::cin.getline(name, MAX_STR_LEN);

            char author[MAX_STR_LEN];
            std::cout << "|-> Author: ";
            std::cin.getline(author, MAX_STR_LEN);

            char ISBN[MAX_STR_LEN];
            std::cout << "|-> ISBN: ";
            std::cin.getline(ISBN, MAX_STR_LEN);

            // Selecting which print mode should be used
            unsigned int modeNumber;
            std::cout << "|-> Reading mode (0: whole book, 1: pages, 2: sentences): ";
            std::cin >> modeNumber;
            std::cin.ignore();

            if (modeNumber > 2) {
                std::cerr << "ERR: Invalid mode number!\n";
                continue;
            }

            // If PAGES mode is selected -> get user input for how many lines per page should be printed
            unsigned int linesCount;
            if ((ReadingMode) modeNumber == PAGES) {
                std::cout << "|-> Lines per page: ";
                std::cin >> linesCount;
                std::cin.ignore();
            }

            // Search for the book in the library
            Book *book = library.findBook(name, author, ISBN, "");
            if (book == nullptr) {
                std::cerr << "ERR: Book not found!\n";
                continue;
            }

            // If the book is found -> print its information and start printing its content in the mode specified
            std::cout << *book << '\n';
            Library::printBookContent(book, (ReadingMode) modeNumber, linesCount);

            continue;
        }

        // Command for exiting the program
        if (!std::strcmp(command, "exit")) {
            break;
        }
    }

    std::cout << '\n';

    return 0;
}

