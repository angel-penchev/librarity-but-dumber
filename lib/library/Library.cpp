//
// Created by apenchev on 5/4/2022.
//

#include "../../include/library/Library.h"
#include "../../include/helpers/StringHelper.h"

/**
 * Library default constructor.
 */
Library::Library() : books(new Book[0]), users(new User[0]), booksFilename(), usersFilename() {
    this->setBooksFilename("");
    this->setUsersFilename("");
}

/**
 * Library parameter constructor.
 * @param booksFilename Filename of the books binary file
 * @param usersFilename Filename of the users binary file
 */
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

/**
 * Library copy-constructor.
 * @param other Reference to another Library object
 */
Library::Library(const Library &other) : books(), users(), booksFilename(), usersFilename() {
    this->copy(other);
}

/**
 * Equality "=" operator override.
 * @param other Reference to another Library object
 * @return Reference to self
 */
Library &Library::operator=(const Library &other) {
    if (this != &other) {
        this->clear();
        this->copy(other);
    }
    return *this;
}

/**
 * Library destructor.
 */
Library::~Library() {
    this->clear();
}

/**
 * Adds a book to the books array.
 * @param book Book to be added
 * @return Reference to the added book
 */
Book *Library::addBook(const Book &book) {
    // Verify a book with the same ISBN doesn't exist
    if (this->findBookIndex(book.getISBN(), FindMode::FIND_BY_ISBN) >= 0) {
        throw LibraryException(LibraryErrorCode::DUPLICATE_ISBN);
    }

    // Allocate a new array with increased size
    Book *newArr = new Book[this->booksCount + 1];

    // Copy all book to the new array and add the new one to the end
    for (unsigned int i = 0; i < this->booksCount; i++) {
        newArr[i] = this->books[i];
    }
    newArr[this->booksCount] = book;

    // Delete the old array and set the object one
    delete[] this->books;
    this->books = newArr;

    // Return a reference to the added book
    return &this->books[this->booksCount++];
}

/**
 * Adds an user to the
 * @param user User to be added
 * @return Reference to the added user
 */
User *Library::addUser(const User &user) {
    // Verify a user with the same username doesn't exist
    if (this->findUserIndex(user.getUsername()) >= 0) {
        throw LibraryException(LibraryErrorCode::DUPLICATE_USERNAME);
    }

    // Allocate a new array with increased size
    User *newArr = new User[this->usersCount + 1];

    // Copy all users to the new array and add the new one to the end
    for (unsigned int i = 0; i < this->usersCount; i++) {
        newArr[i] = this->users[i];
    }
    newArr[this->usersCount] = user;

    // Delete the old array and set the object one
    delete[] this->users;
    this->users = newArr;

    // Return a reference to the added user
    return &this->users[this->usersCount++];
}

/**
 * Case-insensitive books search by criteria.
 * @param query
 * @param findMode Whether to search by name, author, ISBN or description snippet
 * @return Pointer to the book found
 */
Book *Library::findBook(const char *query, FindMode findMode) const {
    // Try to find the book index in books
    int bookIndex = this->findBookIndex(query, findMode, false);

    // If the index is less than 0 -> the book was not found
    if (bookIndex < 0) {
        return nullptr;
    }

    // Return a pointer to the book
    return &this->books[bookIndex];
}

/**
 * Delete a book from books.
 * @param ISBN ISBN identificator of the book to be deleted
 * @param deleteContentsFile Whether to delete the contents file or not
 */
void Library::removeBook(const char *ISBN, const bool deleteContentsFile) {
    // Try to find the book index in books
    int bookIndex = this->findBookIndex(ISBN, FindMode::FIND_BY_ISBN);

    // If the index is less than 0 -> the book was not found
    if (bookIndex < 0) {
        throw LibraryException(LibraryErrorCode::BOOK_NOT_FOUNT_ERR);
    }

    // Delete the contents file if requested
    if (deleteContentsFile) {
        this->books[bookIndex].deleteBookContents();
    }

    // Create a new array with one space removed
    Book *newArr = new Book[--this->booksCount];

    // Copy all books before the index in the new array
    for (unsigned int i = 0; i < bookIndex; i++) {
        newArr[i] = this->books[i];
    }

    // Copy all books after the index in the new array
    for (unsigned int i = bookIndex; i < this->booksCount; i++) {
        newArr[i] = this->books[i + 1];
    }

    // Delete the old array and set the object one
    delete[] this->books;
    this->books = newArr;
}

/**
 * Sort books by criteria.
 * @param sortingMode Whether to sort by name, author or rating.
 */
void Library::sortBooks(SortingMode sortingMode) {
    for (int i = 0; i < (int) this->booksCount - 1; i++) {
        for (int j = i + 1; j < (int) this->booksCount; j++) {
            bool swapCondition;
            switch (sortingMode) {
                case SortingMode::SORT_BY_NAME:
                    swapCondition = std::strcmp(this->books[i].getName(), this->books[j].getName()) > 0;
                    break;
                case SortingMode::SORT_BY_AUTHOR:
                    swapCondition = std::strcmp(this->books[i].getAuthor(), this->books[j].getAuthor()) > 0;
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

/*
 * Print information for every book in books.
 */
void Library::printBooks() const {
    for (unsigned int i = 0; i < this->booksCount; i++) {
        std::cout << this->books[i];
    }
}

/**
 * Prints the contents of a book.
 * @param book Book whose contents to be printed
 * @param readingMode Whether to print the entire book at once, with page separation or with sentence separation.
 * @param linesCount Lines in a book page
 */
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

/**
 * Updates the books binary file with the current books array content.
 */
void Library::updateBooksFile() const {
    std::ofstream booksFile(this->booksFilename, std::ios::binary | std::ios::out | std::ios::trunc);
    booksFile.write((const char *) &this->booksCount, sizeof(this->booksCount));
    for (unsigned int i = 0; i < this->booksCount; i++) {
        booksFile << this->books[i];
    }
    booksFile.close();
}

/**
 * Updates the user binary file with the current books array content.
 */
void Library::updateUsersFile() const {
    std::ofstream usersFile(this->usersFilename, std::ios::binary | std::ios::out | std::ios::trunc);
    usersFile.write((const char *) &this->usersCount, sizeof(this->usersCount));
    for (unsigned int i = 0; i < this->usersCount; i++) {
        usersFile << this->users[i];
    }
    usersFile.close();
}


/**
 * Attempt to login a user with username and password credentials.
 * @param username Username to attempt login with
 * @param password Password to attempt login with
 * @return Pointer to the user on successful login, otherwise nullptr
 */
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

/**
 * Change user password.
 * @param username User username
 * @param oldPassword Old user password
 * @param newPassword New password to be set
 * @param newPasswordConfirm Confirmation of the new password
 */
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


/**
 * Library books getter.
 * @return Library books array
 */
Book *Library::getBooks() const {
    return books;
}

/**
 * Library books setter.
 * @param newBooks Books array to be copied
 * @param size Size of the books array
 */
void Library::setBooks(Book *newBooks, unsigned int size) {
    this->books = new Book[size];
    this->booksCount = size;

    for (unsigned int i = 0; i < size; i++) {
        this->books[i] = newBooks[i];
    }
}

/**
 * Library users getter.
 * @return Library users array
 */
User *Library::getUsers() const {
    return users;
}

/**
 * Library users setter.
 * @param newUsers Users array to be copied
 * @param size Size of the books array
 */
void Library::setUsers(User *newUsers, unsigned int size) {
    this->users = new User[size];
    this->usersCount = size;

    for (unsigned int i = 0; i < size; i++) {
        this->users[i] = newUsers[i];
    }
}

/**
 * Library books filename getter.
 * @return Books filename to be set
 */
char *Library::getBooksFilename() const {
    return this->booksFilename;
}

/**
 * Library books filename setter.
 * @param newBooksFilename Users filename to be set
 */
void Library::setBooksFilename(const char *newBooksFilename) {
    // Verifying input is not null
    if (newBooksFilename == nullptr) {
        return;
    }

    // Allocating memory and copying the input books filename
    this->booksFilename = new char[std::strlen(newBooksFilename) + 1];
    std::strncpy(this->booksFilename, newBooksFilename, std::strlen(newBooksFilename) + 1);
}

/**
 * Library users filename getter.
 * @return Library users filename
 */
char *Library::getUsersFilename() const {
    return this->usersFilename;
}

/**
 * Library users filename setter.
 * @param newUsersFilename Users filename to be set
 */
void Library::setUsersFilename(const char *newUsersFilename) {
    // Verifying input is not null
    if (newUsersFilename == nullptr) {
        return;
    }

    // Allocating memory and copying the input users filename
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

/**
 * Finds the index of a user in the users array by their username.
 * @param query Query to search with.
 * @param findMode Whether to search by name, author, ISBN or description snippet
 * @param isCaseSensitive Whether letter casing matters or not
 * @param startingPosition Where in the array to start the search
 * @return Index of the book in the array or -1 on failure
 */
int
Library::findBookIndex(const char *query, FindMode findMode, bool isCaseSensitive, unsigned int startingPosition) const {
    const char *searchQuery = isCaseSensitive ? query : StringHelper::toLowercase(query);
    for (unsigned int i = startingPosition; i < this->booksCount; i++) {
        bool findCondition;
        switch (findMode) {
            case FindMode::FIND_BY_NAME:
                if (isCaseSensitive) {
                    findCondition = !std::strcmp(this->books[i].getName(), searchQuery);
                    break;
                }

                {
                    const char *lowercaseName = StringHelper::toLowercase(this->books[i].getName());
                    findCondition = !std::strcmp(lowercaseName, searchQuery);
                    delete[] lowercaseName;
                }
                break;
            case FindMode::FIND_BY_AUTHOR:
                if (isCaseSensitive) {
                    findCondition = !std::strcmp(this->books[i].getAuthor(), searchQuery);
                    break;
                }

                {
                    const char *lowercaseAuthor = StringHelper::toLowercase(this->books[i].getAuthor());
                    findCondition = !std::strcmp(lowercaseAuthor, searchQuery);
                    delete[] lowercaseAuthor;
                }
                
                break;
            case FindMode::FIND_BY_ISBN:
                if (isCaseSensitive) {
                    findCondition = !strcmp(this->books[i].getISBN(), searchQuery);
                    break;
                }

                {
                    const char *lowercaseISBN = StringHelper::toLowercase(this->books[i].getISBN());
                    findCondition = !std::strcmp(lowercaseISBN, query);
                    delete[] lowercaseISBN;
                }

                break;
            case FindMode::FIND_BY_DESCRIPTION_SNIPPET:
                if (isCaseSensitive) {
                    findCondition = std::strstr(this->books[i].getDescription(), searchQuery) != nullptr;
                    break;
                }

                {
                    const char *lowercaseDescription = StringHelper::toLowercase(this->books[i].getDescription());
                    findCondition = std::strstr(lowercaseDescription, query) != nullptr;
                    delete[] lowercaseDescription;
                }
                break;
        }

        if (findCondition) {
            if (!isCaseSensitive) {
                delete[] searchQuery;
            }
            return (int) i;
        }
    }

    if (!isCaseSensitive) {
        delete[] searchQuery;
    }
    return -1;
}

/**
 * Finds the index of a user in the users array by their username.
 * @param username Username to search with.
 * @return Index of the user in the array or -1 on failure
 */
int Library::findUserIndex(const char *username) const {
    for (unsigned int i = 0; i < this->usersCount; i++) {
        if (!std::strcmp(this->users[i].getUsername(), username)) {
            return (int) i;
        }
    }

    return -1;
}

/**
 * Sets object properties from another Library object.
 * @param other Reference to another Library object
 */
void Library::copy(const Library &other) {
    this->setBooks(other.getBooks(), other.getBooksCount());
    this->setUsers(other.getUsers(), other.getUsersCount());
    this->setBooksFilename(other.getBooksFilename());
    this->setUsersFilename(other.getUsersFilename());
    this->setBooksCount(other.getBooksCount());
    this->setUsersCount(other.getUsersCount());
}

/**
 * Frees dynamically allocated object memory.
 */
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
