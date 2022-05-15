/**
 * Updates the contents file of the Book from a string.
 * @param line Line to be written
 * @param isTruncateMode Whether to delete previous file contents or not
 */
void Book::updateContents(const char *line, bool isTruncateMode) const {
    // Open contents file for writing
    std::ofstream booksContentsFile(
            this->filename, std::ios::out | (isTruncateMode ? std::ios::trunc : std::ios::app));
    if (!booksContentsFile) {
        throw BookException(BookErrorCode::CONTENTS_FILE_WRITING_ERR);
    }

    // Write the text input to the text file
    unsigned int lineLength = std::strlen(line) + 1;
    booksContentsFile.write(line, lineLength) << '\n';

    // Close the contents file
    booksContentsFile.close();
}

/**
 * Updates the contents file of the Book from a text file input stream.
 * @param input Input stream to copy from
 * @param isTruncateMode Whether to delete previous file contents or not
 */
void Book::updateContents(std::ifstream &input, bool isTruncateMode) const {
    // Open contents file for writing
    std::ofstream booksContentsFile(
            this->filename, std::ios::out | (isTruncateMode ? std::ios::trunc : std::ios::app));
    if (!booksContentsFile) {
        throw BookException(CONTENTS_FILE_WRITING_ERR);
    }

    // Copy the contents of the input file to the book contents file
    booksContentsFile << input.rdbuf();

    // Close the contents file
    booksContentsFile.close();
}