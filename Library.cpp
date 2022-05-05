//
// Created by apenchev on 5/4/2022.
//

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
    this->books[++booksCount] = book;

    delete[] this->books;
    this->books = newArr;
}

void Library::addUser(const User& user) {
    User* newArr = new User[this->usersCount + 1];

    for (int i = 0; i < this->usersCount; i++) {
        newArr[i] = this->users[i];
    }
    this->users[++usersCount] = user;

    delete[] this->users;
    this->users = newArr;
}
