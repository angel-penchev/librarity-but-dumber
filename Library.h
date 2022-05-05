//
// Created by apenchev on 5/4/2022.
//

#ifndef LIBRARITY_BUT_DUMBER_LIBRARY_H
#define LIBRARITY_BUT_DUMBER_LIBRARY_H


#include "Book.h"
#include "User.h"

class Library {
private:
    Book *books;
    User *users;
    unsigned int booksCount = 0;
    unsigned int usersCount = 0;
public:
    Library(std::ifstream& inBooks, std::ifstream& inUsers);

    void addBook(const Book& book);

    void addUser(const User& user);
};



#endif //LIBRARITY_BUT_DUMBER_LIBRARY_H
