//
// Created by apenchev on 5/9/2022.
//
#include <cstring>
#include "gtest/gtest.h"
#include "book/Book.h"

class BookFixture : public ::testing::Test {
protected:
    Book *book;

    const char *name = "gosho";
    const char *author = "losho";
    const char *description = "never gonna give you up";
    const unsigned int rating = 8;
    const char *ISBN = "9780000000000";
    const char *filename = "gosho.txt";

    void SetUp() override {
        book = new Book(name, author, description, rating, ISBN, filename);
    }

    void TearDown() override {
        delete book;
    }
};

TEST(BookTestSuite, ShouldExposeADefaultConstructor) {
    Book book;

    ASSERT_STREQ(book.getName(), "Untitled");
    ASSERT_STREQ(book.getAuthor(), "Unknown author");
    ASSERT_STREQ(book.getDescription(), "");
    ASSERT_EQ(book.getRating(), 0);
    ASSERT_STREQ(book.getISBN(), "9780000000000");
    ASSERT_STREQ(book.getFilename(), "");
}

TEST_F(BookFixture, ShouldExposeAConstructorAcceptingParameterValues) {
    ASSERT_STREQ(book->getName(), name);
    ASSERT_STREQ(book->getAuthor(), author);
    ASSERT_STREQ(book->getDescription(), description);
    ASSERT_EQ(book->getRating(), rating);
    ASSERT_STREQ(book->getISBN(), ISBN);
    ASSERT_STREQ(book->getFilename(), filename);
}
