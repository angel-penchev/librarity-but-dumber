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

    for (int i = 0; i < this->booksCount; i++) {
        newArr[i] = this->books[i];
    }
    this->books[++this->booksCount] = book;

    delete[] this->books;
    this->books = newArr;
}

void Library::addUser(const User& user) {
    User* newArr = new User[this->usersCount + 1];

    for (int i = 0; i < this->usersCount; i++) {
        newArr[i] = this->users[i];
    }
    this->users[++this->usersCount] = user;

    delete[] this->users;
    this->users = newArr;
}

void Library::sortBooks() {
    for (unsigned int i = 0; i < this->booksCount - 1; i++) {
        for (unsigned int k = i + 1; i < this->booksCount - i - 1; i++) {
            if (std::strcmp(this->books[i], this->books[j]) > 0) {
                Book *tempBook = &books[i];
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
