//
// Created by apenchev on 5/4/2022.
//

#include "../../include/library/Library.h"
#include "../../include/helpers/StringHelper.h"

Library::Library() : books(new Book[0]), users(new User[0]), booksFilename(), usersFilename() {
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

Library::Library(const Library &other) : books(), users(), booksFilename(), usersFilename() {
    this->copy(other);
}

Library &Library::operator=(const Library &other) {
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
    // Verify a book with the same ISBN doesn't exist
    if (this->findUserIndex(book.getISBN()) >= 0) {
        throw LibraryException(LibraryErrorCode::DUPLICATE_ISBN);
    }

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
    // Verify a user with the same username doesn't exist
    if (this->findUserIndex(user.getUsername()) >= 0) {
        throw LibraryException(LibraryErrorCode::DUPLICATE_USERNAME);
    }

    User *newArr = new User[this->usersCount + 1];

    for (unsigned int i = 0; i < this->usersCount; i++) {
        newArr[i] = this->users[i];
    }
    newArr[this->usersCount] = user;

    delete[] this->users;
    this->users = newArr;

    return &this->users[this->usersCount++];
}

Book *Library::findBook(const char *query, FindMode findMode) const {
    int bookIndex = this->findBookIndex(query, findMode);

    if (bookIndex < 0) {
        return nullptr;
    }

    return &this->books[bookIndex];
}

void Library::removeBook(const char *ISBN, const bool deleteContentsFile) {
    int bookIndex = this->findBookIndex(ISBN, FindMode::FIND_BY_ISBN);

    if (bookIndex < 0) {
        throw LibraryException(LibraryErrorCode::BOOK_NOT_FOUNT_ERR);
    }

    if (deleteContentsFile) {
        this->books[bookIndex].deleteBookContents();
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
}

void Library::sortBooks(SortingMode sortingMode) {
    for (int i = 0; i < (int) this->booksCount - 1; i++) {
        for (int j = i + 1; j < (int) this->booksCount; j++) {
            bool swapCondition;
            switch (sortingMode) {
                case SortingMode::SORT_BY_NAME: {
                    const char *lowercaseNameLeft = StringHelper::toLowercase(this->books[i].getName());
                    const char *lowercaseNameRight = StringHelper::toLowercase(this->books[j].getName());
                    swapCondition = std::strcmp(lowercaseNameLeft, lowercaseNameRight) > 0;
                    delete[] lowercaseNameLeft;
                    delete[] lowercaseNameRight;
                }
                    break;
                case SortingMode::SORT_BY_AUTHOR: {
                    const char *lowercaseAuthorLeft = StringHelper::toLowercase(this->books[i].getAuthor());
                    const char *lowercaseAuthorRight = StringHelper::toLowercase(this->books[j].getAuthor());
                    swapCondition = std::strcmp(this->books[i].getAuthor(), this->books[j].getAuthor()) > 0;
                    delete[] lowercaseAuthorLeft;
                    delete[] lowercaseAuthorRight;
                }
                    break;
                case SortingMode::SORT_BY_RATING:
                    swapCondition = this->books[i].getRating() > this->books[j].getRating();
                    break;
            }

            if (swapCondition) {
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
        case ReadingMode::WHOLE_BOOK:
            book->printAllContents();
            break;
        case ReadingMode::PAGES:
            book->printPaginatedContents(linesCount);
            break;
        case ReadingMode::SENTENCES:
            book->printSentenceSeparatedContents();
            break;
        default:
            throw std::invalid_argument("Unimplemented item");
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

void Library::changeUserPassword(const char *username, const char *oldPassword, const char *newPassword,
                                 const char *newPasswordConfirm) const {
    // Find the user by username
    int userIndex = this->findUserIndex(username);
    if (userIndex < 0) {
        throw LibraryException(LibraryErrorCode::BOOK_NOT_FOUNT_ERR);

    }

    // Verifying the old password matches the one stored
    if (!this->users[userIndex].verifyPassword(oldPassword)) {
        throw LibraryException(LibraryErrorCode::INVALID_OLD_PASSWORD);
    }

    // Verifying the new password and its confirmation match
    if (std::strcmp(newPassword, newPasswordConfirm) != 0) {
        throw LibraryException(LibraryErrorCode::MISMATCHING_PASSWORDS_ERR);
    }

    // Change the password
    this->users[userIndex].setPassword(newPassword);

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
Library::findBookIndex(const char *query, FindMode findMode, unsigned int startingPosition) const {
    for (unsigned int i = startingPosition; i < this->booksCount; i++) {
        bool findCondition;
        switch (findMode) {
            case FindMode::FIND_BY_NAME:
                findCondition = !std::strcmp(this->books[i].getName(), query);
                break;
            case FindMode::FIND_BY_AUTHOR:
                findCondition = !std::strcmp(this->books[i].getAuthor(), query);
                break;
            case FindMode::FIND_BY_ISBN:
                findCondition = !strcmp(this->books[i].getISBN(), query);
                break;
            case FindMode::FIND_BY_DESCRIPTION_SNIPPET:
                findCondition = std::strstr(this->books[i].getDescription(), query) != nullptr;
                break;
        }

        if (findCondition) {
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
