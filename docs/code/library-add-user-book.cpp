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