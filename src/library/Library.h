//
// Created by apenchev on 5/4/2022.
//

#ifndef LIBRARITY_BUT_DUMBER_LIBRARY_H
#define LIBRARITY_BUT_DUMBER_LIBRARY_H


#include "../book/Book.h"
#include "../user/User.h"

class Library {
private:
    Book *books;
    User *users;
    std::fstream &booksFile;
    std::fstream &usersFile;
    unsigned int booksCount = 0;
    unsigned int usersCount = 0;

    int findBookIndex(const char *name, const char *author, const char *ISBN, const char *descriptionSnippet) const;

public:
    Library(std::fstream &booksFile, std::fstream &usersFile);

    void addBook(const Book &book);

    void addUser(const User &user);

    Book *findBook(const char *name, const char *author, const char *ISBN, const char *descriptionSnippet) const;

    bool removeBook(const char *name, const char *author, const char *ISBN, const char *descriptionSnippet);

    void sortBooks();

    void printBooks() const;

    void updateBooksFile() const;

    void updateUsersFile() const;
};


#endif //LIBRARITY_BUT_DUMBER_LIBRARY_H
