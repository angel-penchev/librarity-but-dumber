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
    unsigned int booksCount = 0;
    unsigned int usersCount = 0;

    int findBookIndex(const char *name, const char *author, const char *ISBN, const char *descriptionSnippet);
public:
    Library(std::ifstream& inBooks, std::ifstream& inUsers);

    void addBook(const Book& book);

    void addUser(const User& user);

    Book* findBook(const char *name, const char *author, const char *ISBN, const char *descriptionSnippet);

    bool removeBook(const char *name, const char *author, const char *ISBN, const char *descriptionSnippet);

    void sortBooks();

    void printBooks();
};



#endif //LIBRARITY_BUT_DUMBER_LIBRARY_H
