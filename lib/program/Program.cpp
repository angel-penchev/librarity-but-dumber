//
// Created by apenchev on 5/12/2022.
//

#include "../../include/program/Program.h"

int Program::run() {
    // Set binary file locations and initialize a library object
    const char *BOOKS_FILENAME = "books.bin";
    const char *USERS_FILENAME = "users.bin";

    Library library = Library(BOOKS_FILENAME, USERS_FILENAME);

    // Attempt to login user
    char usernameInput[MAX_STR_LEN];
    char passwordInput[MAX_STR_LEN];
    User *userPtr;

    // Getting userPtr username input
    std::cout << "Username: ";
    std::cin.getline(usernameInput, MAX_STR_LEN);

    for (unsigned int i = 0; i < MAX_PWD_ATTEMPTS; i++) {
        // Getting userPtr password input
        std::cout << "Password: ";
        PasswordHelper::inputPassword(&passwordInput[0], MAX_STR_LEN);

        // Attempt logging in with the submitted credentials
        userPtr = library.loginUser(usernameInput, passwordInput);

        // Break out of the password loop if the login is successful
        if (userPtr != nullptr) {
            break;
        }

        // Show a warning for invalid password
        std::cerr << "WARN: Invalid password! You have " << MAX_PWD_ATTEMPTS - i - 1 << " attempts left.\n";
    }

    // Authentication failed if the userPtr is null after 3 password inputs
    if (userPtr == nullptr) {
        std::cerr << "ERR: Failed to authenticate userPtr!\n";
        return 1;
    }

    User user = *userPtr;
    char command[MAX_CMD_LEN];
    while (std::cout << "|> " && std::cin.getline(command, MAX_CMD_LEN)) {
        // Command for adding a user to the library
        if (!std::strcmp(command, "add user")) {
            Program::addUserCommand(library, user.isAdministrator());
            continue;
        }

        // Command for changing your own password
        if (!std::strcmp(command, "change password")) {
            Program::changePasswordCommand(library, user.getUsername());
            continue;
        }

        // Command for adding a book to the library
        if (!std::strcmp(command, "add") || !std::strcmp(command, "add book")) {
            Program::addBookCommand(library, user.isAdministrator());
            continue;
        }

        // Command for removing a book from the library
        if (!std::strcmp(command, "remove")) {
            Program::removeBookCommand(library, user.isAdministrator());
            continue;
        }

        // Command for outputting all books in the library
        if (!std::strcmp(command, "view")) {
            Program::viewCommand(library);
            continue;
        }

        // Command for sorting and outputting all books in the library
        if (!std::strcmp(command, "sort")) {
            Program::sortCommand(library);
            continue;
        }

        // Command for searching for a book and printing its information
        if (!std::strcmp(command, "find") || !std::strcmp(command, "search")) {
            Program::findCommand(library);
            continue;
        }

        if (!std::strcmp(command, "print")) {
            Program::printCommand(library);
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

void Program::addUserCommand(Library &library, bool isAdministrator) {
    // Validating whether the current user is administrator or not
    if (!isAdministrator) {
        std::cerr << "ERR: Admin privileges required!\n";
        return;
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

void Program::changePasswordCommand(Library &library, const char *username) {
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
        library.changeUserPassword(username, oldPassword, newPassword, newPasswordConfirm);
    } catch (LibraryException &exception) {
        std::cerr << "ERR: " << exception.getErrorMessage() << '\n';
        return;
    }
}

void Program::addBookCommand(Library library, bool isAdministrator) {
// Validating whether the current user is isAdministrator or not
    if (!isAdministrator) {
        std::cerr << "ERR: Admin privileges required!\n";
        return;
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
            return;
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
                    return;
                }

                // Copy contents from source file and close it
                book->updateContents(sourceFile);
                sourceFile.close();
                break;
        }
    } catch (const BookException &exception) {
        std::cerr << "ERR: " << exception.getErrorMessage() << '\n';
        return;
    }
}

void Program::removeBookCommand(Library library, bool isAdministrator) {
    // Validating whether the current user is administrator or not
    if (!isAdministrator) {
        std::cerr << "ERR: Admin privileges required!\n";
        return;
    }

    // Search criteria for the book to be removed
    char ISBN[MAX_STR_LEN];
    do {
        std::cout << "|-> ISBN: ";
        std::cin.getline(ISBN, MAX_STR_LEN);

        if (!Book::isValidISBN(ISBN)) {
            std::cerr << "ERR: Invalid ISBN!\n";
        }
    } while (!Book::isValidISBN(ISBN));

    // Whether to delete the contents file or not
    char deleteContentsChar;
    std::cout << "|-> Delete book contents file (y/n): ";
    std::cin >> deleteContentsChar;
    std::cin.ignore();
    bool deleteContents = deleteContentsChar == 'Y' || deleteContentsChar == 'y';

    // Search for the book and remove it if it's found
    try {
        library.removeBook(ISBN, deleteContents);
    } catch (LibraryException &exception) {
        std::cerr << "ERR: " << exception.getErrorMessage() << '\n';
        return;
    } catch (BookException &exception) {
        std::cerr << "ERR: " << exception.getErrorMessage() << '\n';
        return;
    }

    // Update the books file if the book is removed
    library.updateBooksFile();
}

void Program::viewCommand(const Library& library) {
    library.printBooks();
}

void Program::sortCommand(Library library) {
    // Selecting which print mode should be used
    unsigned int modeNumber;
    do {
        std::cout << "|-> Sorting mode (0: by name, 1: by author, 2: by rating): ";
        std::cin >> modeNumber;
        std::cin.ignore();
        if (modeNumber > 2) {
            std::cerr << "ERR: Invalid mode number! Mode should be 0: by name, 1: by author or 2: by rating.\n";
        }
    } while (modeNumber > 2);

    library.sortBooks((SortingMode) modeNumber);
    library.printBooks();
}

void Program::findCommand(const Library& library) {
    unsigned int modeNumber;
    do {
        std::cout << "|-> Find mode (0: by name, 1: by author, 2: by ISBN, 3: by description snippet): ";
        std::cin >> modeNumber;
        std::cin.ignore();
        if (modeNumber > 3) {
            std::cerr << "ERR: Invalid mode number! "
                      << "Mode should be 0: by name, 1: by author, 2: by ISBN or 3: by description snippet.\n";
        }
    } while (modeNumber > 3);

    char query[MAX_STR_LEN];

    switch ((FindMode) modeNumber) {
        case FindMode::FIND_BY_NAME:
            std::cout << "|-> Name: ";
            std::cin.getline(query, MAX_STR_LEN);
            break;

        case FindMode::FIND_BY_AUTHOR:
            std::cout << "|-> Author: ";
            std::cin.getline(query, MAX_STR_LEN);
            break;

        case FindMode::FIND_BY_ISBN:
            do {
                std::cout << "|-> ISBN: ";
                std::cin.getline(query, MAX_STR_LEN);

                if (!Book::isValidISBN(query)) {
                    std::cerr << "ERR: Invalid ISBN!\n";
                }
            } while (!Book::isValidISBN(query));
            break;

        case FindMode::FIND_BY_DESCRIPTION_SNIPPET:
            std::cout << "|-> Description snippet: ";
            std::cin.getline(query, MAX_STR_LEN);
            break;
    }

    Book *book = library.findBook(query, (FindMode) modeNumber);
    if (book == nullptr) {
        std::cerr << "ERR: Book not found!\n";
        return;
    }
    std::cout << *book;
}

void Program::printCommand(Library library) {
    // User input criteria for the book to print
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
    Book *book = library.findBook(ISBN, FindMode::FIND_BY_ISBN);
    if (book == nullptr) {
        std::cerr << "ERR: Book not found!\n";
        return;
    }

    // If the book is found -> print its information and start printing its content in the mode specified
    std::cout << *book << '\n';
    try {
        Library::printBookContent(book, (ReadingMode) modeNumber, linesCount);
    } catch (BookException &exception) {
        std::cerr << "ERR: " << exception.getErrorMessage() << '\n';
        return;
    }
}
