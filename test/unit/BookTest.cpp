//
// Created by apenchev on 5/9/2022.
//
#include "gtest/gtest.h"
#include "book/Book.h"

TEST(BookTestSuite, ShouldExposeADefaultConstructor) {
    Book book;

    ASSERT_STREQ(book.getName(), "Untitled");
    ASSERT_STREQ(book.getAuthor(), "Unknown author");
    ASSERT_STREQ(book.getDescription(), "");
    ASSERT_EQ(book.getRating(), 0);
    ASSERT_STREQ(book.getISBN(), "9780000000000");
    ASSERT_STREQ(book.getFilename(), "");
}
