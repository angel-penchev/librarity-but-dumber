/**
 * Prints the whole book contents file.
 */
void Book::printAllContents() const {
    // Try to open contents file for reading
    std::ifstream booksContentsFile(this->filename, std::ios::in);
    if (!booksContentsFile) {
        throw BookException(BookErrorCode::CONTENTS_FILE_READING_ERR);
    }

    // Read every line and print it until the end of the file
    while (!booksContentsFile.eof()) {
        char line[MAX_LINE_LEN];
        booksContentsFile.getline(line, MAX_LINE_LEN);
        std::cout << line << '\n';
    }

    // Close the contents file
    booksContentsFile.close();
}

/**
 * Prints a certain amount of lines from the book contents file and waits for input confirmation to continue.
 * @param linesCount Amount of lines to print before pause
 */
void Book::printPaginatedContents(unsigned int linesCount) const {
    // Try to open contents file for reading
    std::ifstream booksContentsFile(this->filename, std::ios::in);
    if (!booksContentsFile) {
        throw BookException(BookErrorCode::CONTENTS_FILE_READING_ERR);
    }

    // Read and print N lines at a time until the end of the file
    while (!booksContentsFile.eof()) {
        for (unsigned int i = 0; i < linesCount; i++) {
            char line[MAX_LINE_LEN];
            booksContentsFile.getline(line, MAX_LINE_LEN);
            std::cout << line << '\n';
        }

        std::cout << "\n-- press enter to continue --\n";
        std::cin.ignore();
    }

    // Close the contents file
    booksContentsFile.close();
}

/**
 * Prints the book 1 sentence at a time, waiting for input confirmation to continue.
 */
void Book::printSentenceSeparatedContents() const {
    // Try to open contents file for reading
    std::ifstream booksContentsFile(this->filename, std::ios::in);
    if (!booksContentsFile) {
        throw BookException(BookErrorCode::CONTENTS_FILE_READING_ERR);
    }

    // Read and print the contents, pausing at sentence separators
    while (!booksContentsFile.eof()) {
        char line[MAX_LINE_LEN];
        booksContentsFile.getline(line, MAX_LINE_LEN, '.');
        std::cout << line << "\n\n-- press enter to continue --\n";
        std::cin.ignore();
    }

    // Close the contents file
    booksContentsFile.close();
}