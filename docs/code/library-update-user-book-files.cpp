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