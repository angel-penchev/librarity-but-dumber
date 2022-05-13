//
// Created by apenchev on 5/12/2022.
//

#include "LibrarityButDumber.h"
#include "book/BookException.h"
#include "library/LibraryException.h"

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
    std::cin.getline(usernameInput, MAX_STR_LEN);

    for (unsigned int i = 0; i < MAX_PWD_ATTEMPTS; i++) {
        // Getting user password input
        std::cout << "Password: ";
        PasswordHelper::inputPassword(&passwordInput[0], MAX_STR_LEN);

        // Attempt logging in with the submitted credentials
        user = library.loginUser(usernameInput, passwordInput);

        // Break out of the password loop if the login is successful
        if (user != nullptr) {
            break;
        }

        // Show a warning for invalid password
        std::cerr << "WARN: Invalid password! You have " << MAX_PWD_ATTEMPTS - i - 1 << " attempts left.\n";
    }

    // Authentication failed if the user is null after 3 password inputs
    if (user == nullptr) {
        std::cerr << "ERR: Failed to authenticate user!\n";
        return 1;
    }

    char command[MAX_CMD_LEN];
    while (std::cout << "|> " && std::cin.getline(command, MAX_CMD_LEN)) {
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
            PasswordHelper::inputPassword(&password[0], MAX_STR_LEN - 1);

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
            PasswordHelper::inputPassword(&oldPassword[0], MAX_STR_LEN);

            char newPassword[MAX_STR_LEN];
            std::cout << "|-> New password: ";
            PasswordHelper::inputPassword(&newPassword[0], MAX_STR_LEN);

            char newPasswordConfirm[MAX_STR_LEN];
            std::cout << "|-> New password (confirm): ";
            PasswordHelper::inputPassword(&newPasswordConfirm[0], MAX_STR_LEN);

            // Changing the user password
            try {
                library.changeUserPassword(user, oldPassword, newPassword, newPasswordConfirm);
            } catch (LibraryException &exception) {
                std::cerr << "ERR: " << exception.getErrorMessage() << '\n';
                continue;
            }
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
            do {
                std::cout << "|-> Rating: ";
                std::cin >> rating;
                std::cin.ignore();

                if (!Book::isValidRating(rating)) {
                    std::cerr << "ERR: Invalid rating!\n";
                }
            } while (!Book::isValidRating(rating));

            char ISBN[MAX_STR_LEN];
            do {
                std::cout << "|-> ISBN: ";
                std::cin.getline(ISBN, MAX_STR_LEN);

                if (!Book::isValidISBN(ISBN)) {
                    std::cerr << "ERR: Invalid ISBN!\n";
                }
            } while (!Book::isValidISBN(ISBN));

            char filename[MAX_STR_LEN];
            std::cout << "|-> Filename: ";
            std::cin.getline(filename, MAX_STR_LEN);

            // Check if the book content file exists and ask whether to override it if it does
            std::ifstream booksContentsFile(filename);
            if (booksContentsFile) {
                booksContentsFile.close();
                char overrideFileChar;
                std::cerr << "WARN: A file with the name \"" << filename << "\" already exists!\n";
                std::cout << "|-> Override file (y/n): ";

                std::cin >> overrideFileChar;
                std::cin.ignore();
                bool overrideFile = overrideFileChar == 'Y' || overrideFileChar == 'y';

                if (!overrideFile) {
                    continue;
                }
            }

            // Selecting which print mode should be used
            unsigned int modeNumber;
            do {
                std::cout << "|-> Content writing mode (0: empty file, 1: console input, 2: copy from file): ";
                std::cin >> modeNumber;
                std::cin.ignore();
                if (modeNumber > 2) {
                    std::cerr << "ERR: Invalid mode number! "
                              << "Mode should be 0: empty file, 1: console input or 2: copy from file.";
                }
            } while (modeNumber > 2);

            try {
                // Create the new book and update the books file
                Book *book = library.addBook(Book(name, author, description, rating, ISBN, filename));
                library.updateBooksFile();

                // Create and fill the book contents file
                switch ((WritingMode) modeNumber) {
                    case WritingMode::NONE:
                        // Write an empty string to the book contents file
                        book->updateContents();
                        break;

                    case WritingMode::STANDARD_IN:
                        std::cout << "Write the book content below (write \"--end--\" or press Ctrl+D to end):\n";

                        // Append new lines to the file until the user exits
                        char line[MAX_CMD_LEN];
                        while (std::cin.getline(line, MAX_CMD_LEN - 1) && std::strcmp(line, "--end--") != 0) {
                            book->updateContents(line, false);
                        }
                        break;

                    case WritingMode::FROM_FILE:
                        // Get filename of the file from which to copy
                        char sourceFilename[MAX_STR_LEN];
                        std::cout << "|-> Source filename: ";
                        std::cin.getline(sourceFilename, MAX_STR_LEN);

                        // Open the source content file
                        std::ifstream sourceFile(sourceFilename, std::ios::in);
                        if (!sourceFile) {
                            std::cerr << "ERR: Source content file could not be opened for reading!\n";
                            book->updateContents(); // Create an empty file on failure
                            continue;
                        }

                        // Copy contents from source file and close it
                        book->updateContents(sourceFile);
                        sourceFile.close();
                        break;
                }
            } catch (const BookException &exception) {
                std::cerr << "ERR: " << exception.getErrorMessage() << '\n';
                continue;
            }

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
            do {
                std::cout << "|-> ISBN: ";
                std::cin.getline(ISBN, MAX_STR_LEN);

                if (!Book::isValidISBN(ISBN)) {
                    std::cerr << "ERR: Invalid ISBN!\n";
                }
            } while (!Book::isValidISBN(ISBN));

            // Search for the book and remove it if it's found
            try {
                library.removeBook(name, author, ISBN);
            } catch (LibraryException &exception) {
                std::cerr << "ERR: " << exception.getErrorMessage() << '\n';
                continue;
            }

            // Update the books file if the book is removed
            library.updateBooksFile();

            continue;
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

        // Command for searching for a book and printing its information
        if (!std::strcmp(command, "find") || !std::strcmp(command, "search")) {
            char name[MAX_STR_LEN];
            std::cout << "|-> Name: ";
            std::cin.getline(name, MAX_STR_LEN);

            char author[MAX_STR_LEN];
            std::cout << "|-> Author: ";
            std::cin.getline(author, MAX_STR_LEN);

            char ISBN[MAX_STR_LEN];
            do {
                std::cout << "|-> ISBN: ";
                std::cin.getline(ISBN, MAX_STR_LEN);

                if (!Book::isValidISBN(ISBN)) {
                    std::cerr << "ERR: Invalid ISBN!\n";
                }
            } while (!Book::isValidISBN(ISBN));

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
            do {
                std::cout << "|-> ISBN: ";
                std::cin.getline(ISBN, MAX_STR_LEN);

                if (!Book::isValidISBN(ISBN)) {
                    std::cerr << "ERR: Invalid ISBN!\n";
                }
            } while (!Book::isValidISBN(ISBN));

            // Selecting which print mode should be used
            unsigned int modeNumber;
            do {
                std::cout << "|-> Reading mode (0: whole book, 1: pages, 2: sentences): ";
                std::cin >> modeNumber;
                std::cin.ignore();
                if (modeNumber > 2) {
                    std::cerr << "ERR: Invalid mode number! Mode should be 0: whole book, 1: pages or 2: sentences.\n";
                }
            } while (modeNumber > 2);

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
            try {
                Library::printBookContent(book, (ReadingMode) modeNumber, linesCount);
            } catch (BookException &exception) {
                std::cerr << "ERR: " << exception.getErrorMessage() << '\n';
                continue;
            }

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
