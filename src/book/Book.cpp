//
// Created by apenchev on 5/4/2022.
//

#include <cstring>
#include "Book.h"

Book::Book(const char *name, const char *author, const char *description, unsigned int rating, const char *ISBN)
        : name(),
          author(),
          description(),
          rating(rating),
          ISBN() {
    this->setName(name);
    this->setAuthor(author);
    this->setDescription(description);
    this->setISBN(ISBN);
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
}

char *Book::getName() const {
    return this->name;
}

void Book::setName(const char *newName) {
    if (newName == nullptr) {
        return;
    }

    delete[] this->name;
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

    delete[] this->author;
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

    delete[] this->description;
    this->description = new char[std::strlen(newDescription) + 1];
    std::strncpy(this->description, newDescription, std::strlen(newDescription) + 1);
}

unsigned int Book::getRating() const {
    return rating;
}

void Book::setRating(unsigned int newRating) {
    this->rating = newRating;
}

char *Book::getISBN() const {
    return this->ISBN;
}

void Book::setISBN(const char *newISBN) {
    if (newISBN == nullptr) {
        return;
    }

    delete[] this->ISBN;
    this->ISBN = new char[std::strlen(newISBN) + 1];
    std::strncpy(this->ISBN, newISBN, std::strlen(newISBN) + 1);
}

void Book::copy(const Book &other) {
    this->setName(other.getName());
    this->setAuthor(other.getAuthor());
    this->setDescription(other.getDescription());
    this->setRating(other.getRating());
    this->setISBN(other.getISBN());
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
}
