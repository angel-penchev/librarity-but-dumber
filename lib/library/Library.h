//
// Created by apenchev on 5/4/2022.
//

#ifndef LIBRARITY_BUT_DUMBER_LIBRARY_H
#define LIBRARITY_BUT_DUMBER_LIBRARY_H

#include <iostream>
#include <cstring>

#include "../book/Book.h"
#include "../user/User.h"
#include "../enums/ReadingMode.h"

class Library {
private:
    Book *books;
    User *users;
    char *booksFilename;
    char *usersFilename;
    unsigned int booksCount = 0;
    unsigned int usersCount = 0;

    int findBookIndex(const char *name, const char *author, const char *ISBN, const char *descriptionSnippet) const;

    int findUserIndex(const char *username) const;

    void copy(const Library &other);

    void clear();

public:
    Library();

    Library(const char *booksFilename, const char *usersFilename);

    Library(const Library &other);

    Library &operator=(const Library &other);

    virtual ~Library();

    Book *addBook(const Book &book);

    User *addUser(const User &user);

    Book *findBook(const char *name, const char *author, const char *ISBN, const char *descriptionSnippet) const;

    void removeBook(const char *name, const char *author, const char *ISBN);

    void sortBooks();

    void printBooks() const;

    static void printBookContent(Book *book, ReadingMode readingMode, unsigned int linesCount = 5);

    void updateBooksFile() const;

    void updateUsersFile() const;

    User *loginUser(const char *username, const char *password) const;

    void
    changeUserPassword(User *user, const char *oldPassword, const char *newPassword,
                       const char *newPasswordConfirm) const;

    Book *getBooks() const;

    void setBooks(Book *newBooks, unsigned int size);

    User *getUsers() const;

    void setUsers(User *newUsers, unsigned int size);

    char *getBooksFilename() const;

    void setBooksFilename(const char *newBooksFilename);

    char *getUsersFilename() const;

    void setUsersFilename(const char *newUsersFilename);

    unsigned int getBooksCount() const;

    void setBooksCount(unsigned int newBooksCount);

    unsigned int getUsersCount() const;

    void setUsersCount(unsigned int newUsersCount);
};


#endif //LIBRARITY_BUT_DUMBER_LIBRARY_H
