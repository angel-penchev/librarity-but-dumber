//
// Created by apenchev on 5/4/2022.
//

#include "../../include/book/Book.h"

/**
 * Book parameter constructor.
 *
 * @param name Name of the Book (default: "Untitled")
 * @param author Name of the Book author **(default: "Unknown author")**
 * @param description Detailed Book description
 * @param rating Overall book rating
 * @param ISBN International Standard Book Number
 * @param filename Location of the book contents file
 */
Book::Book(const char *name, const char *author, const char *description, double rating, const char *ISBN,
           const char *filename)
        : name(),
          author(),
          description(),
          rating(rating),
          ISBN(),
          filename() {
    this->setName(name);
    this->setAuthor(author);
    this->setDescription(description);
    this->setISBN(ISBN);
    this->setFilename(filename);
}

/**
 * Book copy-constructor.
 * @param other Reference to another Book object
 */
Book::Book(const Book &other) : name(), author(), description(), rating(), ISBN(), filename() {
    this->copy(other);
}

/**
 * Book file constructor.
 * Reads the information for a book from a file stream and constructs a Book object based on it.
 * @param in Input file stream
 */
Book::Book(std::istream &in) : name(), author(), description(), rating(), ISBN(), filename() {
    unsigned int nameLength;
    in.read((char *) &nameLength, sizeof(nameLength));
    this->name = new char[nameLength];
    in.read(this->name, nameLength);

    unsigned int authorLength;
    in.read((char *) &authorLength, sizeof(authorLength));
    this->author = new char[authorLength];
    in.read(this->author, authorLength);

    unsigned int descriptionLength;
    in.read((char *) &descriptionLength, sizeof(descriptionLength));
    this->description = new char[descriptionLength];
    in.read(this->description, descriptionLength);

    in.read((char *) &this->rating, sizeof(this->rating));

    unsigned int ISBNLength;
    in.read((char *) &ISBNLength, sizeof(ISBNLength));
    this->ISBN = new char[ISBNLength];
    in.read(this->ISBN, ISBNLength);

    unsigned int filenameLength;
    in.read((char *) &filenameLength, sizeof(filenameLength));
    this->filename = new char[filenameLength];
    in.read(this->filename, filenameLength);
}

/**
 * Equality "=" operator override.
 * @param other Reference to another Book object
 * @return Reference to self
 */
Book &Book::operator=(const Book &other) {
    if (this != &other) {
        this->clear();
        this->copy(other);
    }
    return *this;
}

/**
 * Output "<<" operator override for output streams.
 * @param os Output stream
 * @param book Reference to a Book object to output
 * @return
 */
std::ostream &operator<<(std::ostream &os, const Book &book) {
    os << "Name: " << book.name << ", Author: " << book.author << ", Rating: " << book.rating << ", ISBN: "
       << book.ISBN << '\n';
    return os;
}

/**
 * Output "<<" operator override for output file streams.
 * Serializes the information of a book in a binary output file.
 * @param out Output file stream
 * @param book Reference to a Book object to output
 * @return
 */
std::ofstream &operator<<(std::ofstream &out, const Book &book) {
    unsigned int nameLength = std::strlen(book.name) + 1;
    out.write((const char *) &nameLength, sizeof(nameLength));
    out.write((const char *) book.name, nameLength);

    unsigned int authorLength = std::strlen(book.author) + 1;
    out.write((const char *) &authorLength, sizeof(authorLength));
    out.write((const char *) book.author, authorLength);

    unsigned int descriptionLength = std::strlen(book.description) + 1;
    out.write((const char *) &descriptionLength, sizeof(descriptionLength));
    out.write((const char *) book.description, descriptionLength);

    out.write((const char *) &book.rating, sizeof(book.rating));

    unsigned int ISBNLength = std::strlen(book.ISBN) + 1;
    out.write((const char *) &ISBNLength, sizeof(ISBNLength));
    out.write((const char *) book.ISBN, ISBNLength);

    unsigned int filenameLength = std::strlen(book.filename) + 1;
    out.write((const char *) &filenameLength, sizeof(filenameLength));
    out.write((const char *) book.filename, filenameLength);

    return out;
}

/**
 * Book destructor.
 */
Book::~Book() {
    this->clear();
}

/**
 * Book name getter.
 * @return Book name.
 */
char *Book::getName() const {
    return this->name;
}

/**
 * Book name setter.
 * @param newName Name to be set
 */
void Book::setName(const char *newName) {
    // Verifying input is not null
    if (newName == nullptr) {
        return;
    }

    // Allocating memory and copying the input name
    this->name = new char[std::strlen(newName) + 1];
    std::strncpy(this->name, newName, std::strlen(newName) + 1);
}

/**
 * Book author getter.
 * @return Book author
 */
char *Book::getAuthor() const {
    return this->author;
}

/**
 * Book author setter.
 * @param newAuthor Author to be set
 */
void Book::setAuthor(const char *newAuthor) {
    // Verifying input is not null
    if (newAuthor == nullptr) {
        return;
    }

    // Allocating memory and copying the input author
    this->author = new char[std::strlen(newAuthor) + 1];
    std::strncpy(this->author, newAuthor, std::strlen(newAuthor) + 1);
}

/**
 * Book description getter.
 * @return Book description
 */
char *Book::getDescription() const {
    return this->description;
}

/**
 * Book description setter.
 * @param newDescription Description to be set
 */
void Book::setDescription(const char *newDescription) {
    // Verifying input is not null
    if (newDescription == nullptr) {
        return;
    }

    // Allocating memory and copying the input description
    this->description = new char[std::strlen(newDescription) + 1];
    std::strncpy(this->description, newDescription, std::strlen(newDescription) + 1);
}

/**
 * Book rating getter.
 * @return Book rating
 */
double Book::getRating() const {
    return rating;
}

/**
 * Book rating setter.
 * @param newRating Rating to be set
 */
void Book::setRating(double newRating) {
    // Validate new rating
    Book::validateRating(rating);

    this->rating = newRating;
}

/**
 * Book ISBN getter.
 * @return Book ISBN
 */
char *Book::getISBN() const {
    return this->ISBN;
}

/**
 * Book ISBN setter.
 * @param newISBN ISBN to be set
 */
void Book::setISBN(const char *newISBN) {
    // Verifying input is not null
    if (newISBN == nullptr) {
        return;
    }

    // Validate new ISBN
    Book::validateISBN(newISBN);

    // Allocating memory and copying the input ISBN
    this->ISBN = new char[std::strlen(newISBN) + 1];
    std::strncpy(this->ISBN, newISBN, std::strlen(newISBN) + 1);
}

/**
 * Book filename getter.
 * @return Book contents filename
 */
char *Book::getFilename() const {
    return filename;
}

/**
 * Book filename setter.
 * @param newFilename Contents filename to be set
 */
void Book::setFilename(const char *newFilename) {
    if (newFilename == nullptr) {
        return;
    }

    this->filename = new char[std::strlen(newFilename) + 1];
    std::strncpy(this->filename, newFilename, std::strlen(newFilename) + 1);
}

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

/**
 * Deletes the book contents file
 */
void Book::deleteBookContents() const {
    // Remove contents file
    if (remove(this->filename)) {
        throw BookException(BookErrorCode::CONTENTS_FILE_REMOVAL_ERR);
    }
}

/**
 * Validates rating values.
 * @param newRating Rating to be validated
 */
void Book::validateRating(double newRating) {
    // Rating in proper range
    if (newRating < 0.0 || newRating > 10.0) {
        throw BookException(BookErrorCode::INVALID_RATING_RANGE);
    }
}

/**
 * Validates ISBN values.
 * @param newISBN ISBN to be validated
 */
void Book::validateISBN(const char *newISBN) {
    // ISBN has a valid length
    if (std::strlen(newISBN) != 13) {
        throw BookException(BookErrorCode::INVALID_ISBN_LENGTH);
    }

    // ISBN has a valid GS1 prefix (begins with 978 or 979)
    if (std::strncmp(newISBN, "978", 3) != 0 && std::strncmp(newISBN, "979", 3) != 0) {
        throw BookException(BookErrorCode::INVALID_ISBN_GS1_PREFIX);
    }

    // ISBN checksumCharacter is valid + ISBN only contains numbers
    unsigned int sum = 0;
    for (unsigned int i = 0; i < 12; i++) {
        unsigned int value = newISBN[i] - '0';
        if (value > 9) {
            throw BookException(BookErrorCode::INVALID_ISBN_CHARACTERS);
        }
        sum += value * (i % 2 == 0 ? 1 : 3);
    }

    char checksumCharacter = newISBN[12];
    if (checksumCharacter < '0' || checksumCharacter > '9') {
        throw BookException(BookErrorCode::INVALID_ISBN_CHECKSUM_CHARACTER);
    }

    if (sum % 10 != (checksumCharacter != '0' ? 10 - (checksumCharacter - '0') : 0)) {
        throw BookException(BookErrorCode::INVALID_ISBN_CHECKSUM);
    }
}

/**
 * Validates rating values.
 * @param newRating Rating to be validated
 */
bool Book::isValidRating(double newRating) {
    try {
        Book::validateRating(newRating);
    } catch (BookException &exception) {
        return false;
    }
    return true;
}

/**
 * Validates ISBN values.
 * @param newISBN ISBN to be validated
 */
bool Book::isValidISBN(const char *newISBN) {
    try {
        Book::validateISBN(newISBN);
    } catch (BookException &exception) {
        return false;
    }
    return true;
}

/**
 * Sets object properties from another Book object.
 * @param other Reference to another Book object
 */
void Book::copy(const Book &other) {
    this->setName(other.getName());
    this->setAuthor(other.getAuthor());
    this->setDescription(other.getDescription());
    this->setRating(other.getRating());
    this->setISBN(other.getISBN());
    this->setFilename(other.getFilename());
}

/**
 * Frees dynamically allocated object memory.
 */
void Book::clear() {
    delete[] this->name;
    this->name = nullptr;

    delete[] this->author;
    this->author = nullptr;

    delete[] this->description;
    this->description = nullptr;

    delete[] this->ISBN;
    this->ISBN = nullptr;

    delete[] this->filename;
    this->filename = nullptr;
}
