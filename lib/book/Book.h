//
// Created by apenchev on 5/4/2022.
//

#ifndef LIBRARITY_BUT_DUMBER_BOOK_H
#define LIBRARITY_BUT_DUMBER_BOOK_H

#include <fstream>
#include <ostream>
#include <cstring>
#include <iostream>

#define MAX_LINE_LEN 8196

class Book {
private:
    char *name;
    char *author;
    char *description;
    double rating;
    char *ISBN;
    char *filename;

    void copy(const Book &other);

    void clear();

public:
    Book(const char *name = "Untitled", const char *author = "Unknown author", const char *description = "",
         double rating = 0, const char *ISBN = "9780000000002", const char *filename = "");

    Book(const Book &other);

    Book(std::istream &in);

    Book &operator=(const Book &other);

    friend std::ostream &operator<<(std::ostream &os, const Book &book);

    virtual ~Book();

    void serialize(std::ostream &out);

    char *getName() const;

    void setName(const char *newName);

    char *getAuthor() const;

    void setAuthor(const char *newAuthor);

    char *getDescription() const;

    void setDescription(const char *newDescription);

    double getRating() const;

    void setRating(double newRating);

    char *getISBN() const;

    void setISBN(const char *newISBN);

    char *getFilename() const;

    void setFilename(const char *newFilename);

    void printAllContents() const;

    void printPaginatedContents(unsigned int linesCount) const;

    void printSentenceSeparatedContents() const;

    void updateContents(const char *line = "", bool isTruncateMode = true);

    void updateContents(std::ifstream &input, bool isTruncateMode = true);

    static void validateRating(double newRating);

    static void validateISBN(const char *newISBN);
};


#endif //LIBRARITY_BUT_DUMBER_BOOK_H
