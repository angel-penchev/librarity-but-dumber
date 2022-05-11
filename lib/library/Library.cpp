//
// Created by apenchev on 5/4/2022.
//

#include <iostream>
#include <cstring>
#include "Library.h"

Library::Library(const char *booksFilename, const char *usersFilename) : books(new Book[0]), users(new User[0]),
                                                                         booksFilename(), usersFilename() {
    // Set books and users filename properties
    this->setBooksFilename(booksFilename);
    this->setUsersFilename(usersFilename);

    // Read books from the books binary if it exists
    std::ifstream booksFile(this->booksFilename, std::ios::binary | std::ios::in);
    if (booksFile) {
        unsigned int booksCountFromFile;
        booksFile.read((char *) &booksCountFromFile, sizeof(booksCountFromFile));
        for (unsigned int i = 0; i < booksCountFromFile; i++) {
            this->addBook(Book(booksFile));
        }
    }
    booksFile.close();

    // Try to open users file and read the users from there.
    // If that fails, creating a new users file with a default admin.
    std::ifstream usersFile(usersFilename, std::ios::binary | std::ios::in);
    if (!usersFile) {
        // Add a default administrator to the users
        User defaultAdmin = User("admin", "admin", true);
        this->addUser(defaultAdmin);

        // Create new users file with the administrator
        this->updateUsersFile();
        return;
    }

    // Read users from the books binary
    unsigned int usersCountFromFile;
    usersFile.read((char *) &usersCountFromFile, sizeof(usersCountFromFile));
    for (unsigned int i = 0; i < usersCountFromFile; i++) {
        this->addUser(User(usersFile));
    }
    usersFile.close();
}

Library::~Library() {
    delete[] this->books;
    this->books = nullptr;

    delete[] this->users;
    this->users = nullptr;

    delete[] this->booksFilename;
    this->booksFilename = nullptr;

    delete[] this->usersFilename;
    this->usersFilename = nullptr;
}

void Library::addBook(const Book &book) {
    Book *newArr = new Book[this->booksCount + 1];

    for (unsigned int i = 0; i < this->booksCount; i++) {
        newArr[i] = this->books[i];
    }
    newArr[this->booksCount++] = book;

    delete[] this->books;
    this->books = newArr;
}

void Library::addUser(const User &user) {
    User *newArr = new User[this->usersCount + 1];

    for (unsigned int i = 0; i < this->usersCount; i++) {
        newArr[i] = this->users[i];
    }
    newArr[this->usersCount++] = user;

    delete[] this->users;
    this->users = newArr;
}

Book *Library::findBook(const char *name, const char *author, const char *ISBN, const char *descriptionSnippet) const {
    int bookIndex = this->findBookIndex(name, author, ISBN, descriptionSnippet);

    if (bookIndex < 0) {
        return nullptr;
    }

    return &this->books[bookIndex];
}

bool Library::removeBook(const char *name, const char *author, const char *ISBN) {
    int bookIndex = this->findBookIndex(name, author, ISBN, "");

    if (bookIndex < 0) {
        return false;
    }

    Book *newArr = new Book[--this->booksCount];

    for (unsigned int i = 0; i < bookIndex; i++) {
        newArr[i] = this->books[i];
    }

    for (unsigned int i = bookIndex; i < this->booksCount; i++) {
        newArr[i] = this->books[i + 1];
    }

    delete[] this->books;
    this->books = newArr;

    return true;
}

void Library::sortBooks() {
    for (int i = 0; i < (int) this->booksCount - 1; i++) {
        for (int j = 0; j < (int) this->booksCount - i - 1; j++) {
            if (std::strcmp(this->books[i].getName(), this->books[j].getName()) > 0) {
                Book tempBook = books[i];
                this->books[i] = this->books[j];
                this->books[j] = tempBook;
            }
        }
    }
}

void Library::printBooks() const {
    for (unsigned int i = 0; i < this->booksCount; i++) {
        std::cout << this->books[i];
    }
}

void Library::printBookContent(Book *book, ReadingMode readingMode, unsigned int linesCount) {
    switch (readingMode) {
        case WHOLE_BOOK:
            book->printAllContents();
            break;
        case PAGES:
            book->printPaginatedContents(linesCount);
            break;
        case SENTENCES:
            book->printSentenceSeparatedContents();
            break;
        default:
            std::cerr << "ERR: Invalid reading mode!\n";
            break;
    }
}

void Library::updateBooksFile() const {
    std::ofstream booksFile(this->booksFilename, std::ios::binary | std::ios::out | std::ios::trunc);
    booksFile.write((const char *) &this->booksCount, sizeof(this->booksCount));
    for (unsigned int i = 0; i < this->booksCount; i++) {
        this->books[i].serialize(booksFile);
    }
    booksFile.close();
}

void Library::updateUsersFile() const {
    std::ofstream usersFile(this->usersFilename, std::ios::binary | std::ios::out | std::ios::trunc);
    usersFile.write((const char *) &this->usersCount, sizeof(this->usersCount));
    for (unsigned int i = 0; i < this->usersCount; i++) {
        this->users[i].serialize(usersFile);
    }
    usersFile.close();
}

User *Library::loginUser(const char *username, const char *password) const {
    // Find the user by username
    int userIndex = this->findUserIndex(username);

    // If the user is not found or if the password is incorrect, return nullptr
    if (userIndex < 0 || !this->users[userIndex].verifyPassword(password)) {
        return nullptr;
    }

    // Return the user if login credentials are correct
    return &this->users[userIndex];
}

char *Library::getBooksFilename() const {
    return this->booksFilename;
}

void Library::setBooksFilename(const char *newBooksFilename) {
    if (newBooksFilename == nullptr) {
        return;
    }

    delete[] this->booksFilename;
    this->booksFilename = new char[std::strlen(newBooksFilename) + 1];
    std::strncpy(this->booksFilename, newBooksFilename, std::strlen(newBooksFilename) + 1);
}

char *Library::getUsersFilename() const {
    return this->usersFilename;
}

void Library::setUsersFilename(const char *newUsersFilename) {
    if (newUsersFilename == nullptr) {
        return;
    }

    delete[] this->usersFilename;
    this->usersFilename = new char[std::strlen(newUsersFilename) + 1];
    std::strncpy(this->usersFilename, newUsersFilename, std::strlen(newUsersFilename) + 1);
}

int
Library::findBookIndex(const char *name, const char *author, const char *ISBN, const char *descriptionSnippet) const {
    for (unsigned int i = 0; i < this->booksCount; i++) {
        if (!std::strcmp(this->books[i].getName(), name) &&
            !std::strcmp(this->books[i].getAuthor(), author) &&
            !strcmp(this->books[i].getISBN(), ISBN) &&
            std::strstr(this->books[i].getDescription(), descriptionSnippet) != nullptr) {
            return (int) i;
        }
    }

    return -1;
}

int Library::findUserIndex(const char *username) const {
    for (unsigned int i = 0; i < this->usersCount; i++) {
        if (!std::strcmp(this->users[i].getUsername(), username)) {
            return (int) i;
        }
    }

    return -1;
}
