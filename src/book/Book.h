//
// Created by apenchev on 5/4/2022.
//

#ifndef LIBRARITY_BUT_DUMBER_BOOK_H
#define LIBRARITY_BUT_DUMBER_BOOK_H

#include <fstream>
#include <ostream>

#define MAX_LINE_LEN 8196

class Book {
private:
    char *name;
    char *author;
    char *description;
    unsigned int rating;
    char *ISBN;
    char *filename;

    void copy(const Book &other);

    void clear();

public:
    Book(const char *name = "Untitled", const char *author = "Unknown author", const char *description = "",
         unsigned int rating = 0,
         const char *ISBN = "978-0-00000", const char *filename = "");

    Book(const Book &other);

    Book(std::istream &in);

    Book &operator=(const Book &other);

    virtual ~Book();

    void serialize(std::ostream &out);

    char *getName() const;

    void setName(const char *newName);

    char *getAuthor() const;

    void setAuthor(const char *newAuthor);

    char *getDescription() const;

    void setDescription(const char *newDescription);

    unsigned int getRating() const;

    void setRating(unsigned int newRating);

    char *getISBN() const;

    void setISBN(const char *newISBN);

    char *getFilename() const;

    void setFilename(const char *newFilename);

    void printAllContents() const;

    void printPaginatedContents(unsigned int linesCount) const;

    void printSentenceSeparatedContents() const;

    friend std::ostream &operator<<(std::ostream &os, const Book &book);
};


#endif //LIBRARITY_BUT_DUMBER_BOOK_H
