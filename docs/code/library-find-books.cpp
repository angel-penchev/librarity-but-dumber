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