/*
 * Print information for every book in books.
 */
void Library::printBooks() const {
    for (unsigned int i = 0; i < this->booksCount; i++) {
        std::cout << this->books[i];
    }
}