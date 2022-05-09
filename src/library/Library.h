//
// Created by apenchev on 5/4/2022.
//

#ifndef LIBRARITY_BUT_DUMBER_LIBRARY_H
#define LIBRARITY_BUT_DUMBER_LIBRARY_H


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

public:
    Library(const char *booksFilename, const char *usersFilename);

    virtual ~Library();

    void addBook(const Book &book);

    void addUser(const User &user);

    Book *findBook(const char *name, const char *author, const char *ISBN, const char *descriptionSnippet) const;

    bool removeBook(const char *name, const char *author, const char *ISBN);

    void sortBooks();

    void printBooks() const;

    static void printBookContent(Book *book, ReadingMode readingMode);

    void updateBooksFile() const;

    void updateUsersFile() const;

    char *getBooksFilename() const;

    void setBooksFilename(const char *newBooksFilename);

    char *getUsersFilename() const;

    void setUsersFilename(const char *newUsersFilename);
};


#endif //LIBRARITY_BUT_DUMBER_LIBRARY_H
