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