//
// Created by apenchev on 5/4/2022.
//

#include <iostream>
#include <cstring>
#include "Library.h"

Library::Library(std::ifstream& inBooks, std::ifstream& inUsers) : books(new Book[0]), users(new User[0]) {
    while(!inBooks.eof()) {
        this->addBook(Book(inBooks));
    }

    while(!inUsers.eof()) {
        this->addUser(User(inUsers));
    }
}

void Library::addBook(const Book& book) {
    Book* newArr = new Book[this->booksCount + 1];

    for (unsigned int i = 0; i < this->booksCount; i++) {
        newArr[i] = this->books[i];
    }
    newArr[this->booksCount++] = book;

    delete[] this->books;
    this->books = newArr;
}

void Library::addUser(const User& user) {
    User* newArr = new User[this->usersCount + 1];

    for (unsigned int i = 0; i < this->usersCount; i++) {
        newArr[i] = this->users[i];
    }
    newArr[this->usersCount++] = user;

    delete[] this->users;
    this->users = newArr;
}

Book* Library::findBook(const char *name, const char *author, const char *ISBN, const char *descriptionSnippet) {
    int bookIndex = this->findBookIndex(name, author, ISBN, descriptionSnippet);

    if (bookIndex < 0) {
        return nullptr;
    }

    return &this->books[bookIndex];
}

bool Library::removeBook(const char *name, const char *author, const char *ISBN, const char *descriptionSnippet) {
    int bookIndex = this->findBookIndex(name, author, ISBN, descriptionSnippet);

    if (bookIndex < 0) {
        return false;
    }

    Book* newArr = new Book[--this->booksCount];

    for (unsigned int i = 0; i < bookIndex; i++) {
        newArr[i] = this->books[i];
    }

    for (unsigned int i = bookIndex; i < this->booksCount; i++) {
        newArr[i] = this->books[i + 1];
    }

    delete[] this->books;
    this->books = newArr;
}

void Library::sortBooks() {
    for (unsigned int i = 0; i < this->booksCount - 1; i++) {
        for (unsigned int j = i + 1; j < this->booksCount - i - 1; j++) {
            if (std::strcmp(this->books[i].getName(), this->books[j].getName()) > 0) {
                Book tempBook = books[i];
                this->books[i] = this->books[j];
                this->books[j] = tempBook;
            }
        }
    }
}

void Library::printBooks() {
    for (unsigned int i = 0; i < this->booksCount; i++) {
        std::cout << this->books[i];
    }
}

int Library::findBookIndex(const char *name, const char *author, const char *ISBN, const char *descriptionSnippet) {
    for (unsigned int i = 0; i < this->booksCount; i++) {
        if (!std::strcmp(this->books[i].getName(), name) &&
            !std::strcmp(this->books[i].getAuthor(), author) &&
            !strcmp(this->books[i].getISBN(), ISBN) &&
            std::strstr(this->books[i].getDescription(), descriptionSnippet) != nullptr) {
            return (int) i;
        }
    }

    return -1;
}
