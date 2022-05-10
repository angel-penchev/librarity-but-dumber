//
// Created by apenchev on 5/4/2022.
//

#include <cstring>
#include <iostream>
#include "Book.h"

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

Book::Book(const Book &other) {
    this->copy(other);
}

Book::Book(std::istream &in) {
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

Book &Book::operator=(const Book &other) {
    if (this != &other) {
        this->clear();
        this->copy(other);
    }
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Book &book) {
    os << "Name: " << book.name << ", Author: " << book.author << ", Rating: " << book.rating << ", ISBN: "
       << book.ISBN << '\n';
    return os;
}

Book::~Book() {
    this->clear();
}

void Book::serialize(std::ostream &out) {
    unsigned int nameLength = std::strlen(this->name) + 1;
    out.write((const char *) &nameLength, sizeof(nameLength));
    out.write((const char *) this->name, nameLength);

    unsigned int authorLength = std::strlen(this->author) + 1;
    out.write((const char *) &authorLength, sizeof(authorLength));
    out.write((const char *) this->author, authorLength);

    unsigned int descriptionLength = std::strlen(this->description) + 1;
    out.write((const char *) &descriptionLength, sizeof(descriptionLength));
    out.write((const char *) this->description, descriptionLength);

    out.write((const char *) &this->rating, sizeof(this->rating));

    unsigned int ISBNLength = std::strlen(this->ISBN) + 1;
    out.write((const char *) &ISBNLength, sizeof(ISBNLength));
    out.write((const char *) this->ISBN, ISBNLength);

    unsigned int filenameLength = std::strlen(this->filename) + 1;
    out.write((const char *) &filenameLength, sizeof(filenameLength));
    out.write((const char *) this->filename, filenameLength);
}

char *Book::getName() const {
    return this->name;
}

void Book::setName(const char *newName) {
    if (newName == nullptr) {
        return;
    }

    this->name = new char[std::strlen(newName) + 1];
    std::strncpy(this->name, newName, std::strlen(newName) + 1);
}

char *Book::getAuthor() const {
    return this->author;
}

void Book::setAuthor(const char *newAuthor) {
    if (newAuthor == nullptr) {
        return;
    }

    this->author = new char[std::strlen(newAuthor) + 1];
    std::strncpy(this->author, newAuthor, std::strlen(newAuthor) + 1);
}

char *Book::getDescription() const {
    return this->description;
}

void Book::setDescription(const char *newDescription) {
    if (newDescription == nullptr) {
        return;
    }

    this->description = new char[std::strlen(newDescription) + 1];
    std::strncpy(this->description, newDescription, std::strlen(newDescription) + 1);
}

double Book::getRating() const {
    return rating;
}

void Book::setRating(double newRating) {
    if (newRating < 0.0 || newRating > 10.0) {
        std::cerr << "ERR: Invalid rating! Rating should be between 0.0 and 10.0!\n";
        return;
    }

    this->rating = newRating;
}

char *Book::getISBN() const {
    return this->ISBN;
}

void Book::setISBN(const char *newISBN) {
    if (newISBN == nullptr) {
        return;
    }

    // ISBN has a valid length
    if (std::strlen(newISBN) != 13) {
        std::cerr << "ERR: Invalid ISBN length!\n";
        return;
    }

    // ISBN has a valid GS1 prefix (begins with 978 or 979)
    if (std::strncmp(newISBN, "979", 3) != 0 && std::strncmp(newISBN, "978", 3) != 0) {
        std::cerr << "ERR: Invalid ISBN GS1 prefix!\n";
        return;
    }

    // ISBN checksumCharacter is valid + ISBN only contains numbers
    unsigned int sum = 0;
    for (unsigned int i = 0; i < 12; i++) {
        unsigned int value = newISBN[i] - '0';
        if (value > 9) {
            std::cerr << "ERR: Invalid characters in ISBN!\n";
            return;
        }
        sum += value * (i % 2 == 0 ? 1 : 3);
    }

    char checksumCharacter = newISBN[12];
    if (checksumCharacter < '0' || checksumCharacter > '9') {
        std::cerr << "ERR: Invalid ISBN checksum character!\n";
        return;
    }

    if (sum % 10 != (checksumCharacter != '0' ? 10 - (checksumCharacter - '0') : 0)) {
        std::cerr << "ERR: Invalid ISBN checksum!\n";
        return;
    }

    this->ISBN = new char[std::strlen(newISBN) + 1];
    std::strncpy(this->ISBN, newISBN, std::strlen(newISBN) + 1);
}

char *Book::getFilename() const {
    return filename;
}

void Book::setFilename(const char *newFilename) {
    if (newFilename == nullptr) {
        return;
    }

    this->filename = new char[std::strlen(newFilename) + 1];
    std::strncpy(this->filename, newFilename, std::strlen(newFilename) + 1);
}

void Book::printAllContents() const {
    std::ifstream booksContentsFile(this->filename);
    if (!booksContentsFile) {
        std::cerr << "ERR: Book content file could not be opened for reading!\n";
        return;
    }
    std::cout << booksContentsFile;
    booksContentsFile.close();
}

void Book::printPaginatedContents(unsigned int linesCount) const {
    std::ifstream booksContentsFile(this->filename);
    if (!booksContentsFile) {
        std::cerr << "ERR: Book content file could not be opened for reading!\n";
        return;
    }

    while (!booksContentsFile.eof()) {
        for (unsigned int i = 0; i < linesCount; i++) {
            char line[MAX_LINE_LEN + 1];
            booksContentsFile.getline(line, MAX_LINE_LEN);
            std::cout << line << '\n';
        }

        std::cout << "\n-- press enter to continue --\n";
        std::cin.ignore();
    }

    booksContentsFile.close();
}

void Book::printSentenceSeparatedContents() const {
    std::ifstream booksContentsFile(this->filename, std::ios::in);
    if (!booksContentsFile) {
        std::cerr << "ERR: Book content file could not be opened for reading!\n";
        return;
    }

    while (!booksContentsFile.eof()) {
        char line[MAX_LINE_LEN];
        booksContentsFile.getline(line, MAX_LINE_LEN, '.');
        std::cout << line << "\n\n-- press enter to continue --\n";
        std::cin.ignore();
    }

    booksContentsFile.close();
}

void Book::copy(const Book &other) {
    this->setName(other.getName());
    this->setAuthor(other.getAuthor());
    this->setDescription(other.getDescription());
    this->setRating(other.getRating());
    this->setISBN(other.getISBN());
    this->setFilename(other.getFilename());
}

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
