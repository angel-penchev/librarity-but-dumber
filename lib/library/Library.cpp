//
// Created by apenchev on 5/4/2022.
//

#include "Library.h"

Library::Library() {
    this->books = new Book[0];
    this->users = new User[0];
    this->setBooksFilename("");
    this->setUsersFilename("");
}

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

Library::Library(const Library &other) {
    this->copy(other);
}

Library Library::operator=(const Library &other) {
    if (this != &other) {
        this->clear();
        this->copy(other);
    }
    return *this;
}

Library::~Library() {
    this->clear();
}

Book *Library::addBook(const Book &book) {
    Book *newArr = new Book[this->booksCount + 1];

    for (unsigned int i = 0; i < this->booksCount; i++) {
        newArr[i] = this->books[i];
    }
    newArr[this->booksCount] = book;

    delete[] this->books;
    this->books = newArr;

    return &this->books[this->booksCount++];
}

User *Library::addUser(const User &user) {
    User *newArr = new User[this->usersCount + 1];

    for (unsigned int i = 0; i < this->usersCount; i++) {
        newArr[i] = this->users[i];
    }
    newArr[this->usersCount] = user;

    delete[] this->users;
    this->users = newArr;

    return &this->users[this->usersCount++];
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
        for (int j = i + 1; j < (int) this->booksCount; j++) {
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

void Library::changeUserPassword(User *user, const char *oldPassword, const char *newPassword,
                                 const char *newPasswordConfirm) const {
    // Verifying the old password matches the one stored
    if (!user->verifyPassword(oldPassword)) {
        std::cerr << "ERR: Invalid old password!\n";
        return;
    }

    // Verifying the new password and its confirmation match
    if (std::strcmp(newPassword, newPasswordConfirm) != 0) {
        std::cerr << "ERR: New password doesn't match!\n";
        return;
    }

    // Change the password
    user->setPassword(newPassword);

    // Update users file after the change
    this->updateUsersFile();
}


Book *Library::getBooks() const {
    return books;
}

void Library::setBooks(Book *newBooks, unsigned int size) {
    this->books = new Book[size];

    for (unsigned int i = 0; i < size; i++) {
        this->books[i] = newBooks[i];
    }
}

User *Library::getUsers() const {
    return users;
}

void Library::setUsers(User *newUsers, unsigned int size) {
    this->users = new User[size];

    for (unsigned int i = 0; i < size; i++) {
        this->users[i] = newUsers[i];
    }
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

unsigned int Library::getBooksCount() const {
    return this->booksCount;
}

void Library::setBooksCount(unsigned int newBooksCount) {
    this->booksCount = newBooksCount;
}

unsigned int Library::getUsersCount() const {
    return this->usersCount;
}

void Library::setUsersCount(unsigned int newUsersCount) {
    this->usersCount = newUsersCount;
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

void Library::copy(const Library &other) {
    this->setBooks(other.getBooks(), other.getBooksCount());
    this->setUsers(other.getUsers(), other.getUsersCount());
    this->setBooksFilename(other.getBooksFilename());
    this->setUsersFilename(other.getUsersFilename());
    this->setBooksCount(other.getBooksCount());
    this->setUsersCount(other.getUsersCount());
}

void Library::clear() {
    delete[] this->books;
    this->books = nullptr;

    delete[] this->users;
    this->users = nullptr;

    delete[] this->booksFilename;
    this->booksFilename = nullptr;

    delete[] this->usersFilename;
    this->usersFilename = nullptr;
}
