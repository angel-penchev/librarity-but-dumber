//
// Created by apenchev on 5/9/2022.
//
#include <cstring>
#include "gtest/gtest.h"
#include "book/Book.h"

std::string fixtureDirectoryFilepath = PATH_TO_FIXTURES;
std::string inBookFilepath = fixtureDirectoryFilepath + "inBook.bin";
std::string outBookFilepath = "outBook.bin";

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

TEST_F(BookFixture, ShouldExposeABinaryFileConstructor) {
    // Construct book from binary file
    std::ifstream inFile(inBookFilepath, std::ios::binary | std::ios::in);
    ASSERT_TRUE(inFile);
    Book book = Book(inFile);
    inFile.close();

    // Verify object properties
    ASSERT_STREQ(book.getName(), name);
    ASSERT_STREQ(book.getAuthor(), author);
    ASSERT_STREQ(book.getDescription(), description);
    ASSERT_EQ(book.getRating(), rating);
    ASSERT_STREQ(book.getISBN(), ISBN);
    ASSERT_STREQ(book.getFilename(), filename);
}

TEST_F(BookFixture, ShouldProvideAMethodForSerilizationToABinaryFile) {
    // Serialize a book to a binary file
    std::ofstream outFile(outBookFilepath, std::ios::binary | std::ios::out | std::ios::trunc);
    ASSERT_TRUE(outFile);
    book->serialize(outFile);
    outFile.close();

    // Verify file contents
    std::ifstream resultFile(outBookFilepath, std::ios::binary | std::ios::in);
    ASSERT_TRUE(resultFile);

    unsigned int resultNameLength;
    resultFile.read((char *) &resultNameLength, sizeof(resultNameLength));
    ASSERT_EQ(resultNameLength, strlen(book->getName()) + 1);

    char *resultName = new char[resultNameLength];
    resultFile.read(resultName, resultNameLength);
    ASSERT_STREQ(resultName, book->getName());
    delete[] resultName;

    unsigned int resultAuthorLength;
    resultFile.read((char *) &resultAuthorLength, sizeof(resultAuthorLength));
    ASSERT_EQ(resultAuthorLength, strlen(book->getAuthor()) + 1);

    char *resultAuthor = new char[resultAuthorLength];
    resultFile.read(resultAuthor, resultAuthorLength);
    ASSERT_STREQ(resultAuthor, book->getAuthor());
    delete[] resultAuthor;

    unsigned int resultDescriptionLength;
    resultFile.read((char *) &resultDescriptionLength, sizeof(resultDescriptionLength));
    ASSERT_EQ(resultDescriptionLength, strlen(book->getDescription()) + 1);

    char *resultDescription = new char[resultDescriptionLength];
    resultFile.read(resultDescription, resultDescriptionLength);
    ASSERT_STREQ(resultDescription, book->getDescription());
    delete[] resultDescription;

    unsigned int resultRating;
    resultFile.read((char *) &resultRating, sizeof(resultRating));

    unsigned int resultISBNLength;
    resultFile.read((char *) &resultISBNLength, sizeof(resultISBNLength));
    ASSERT_EQ(resultISBNLength, strlen(book->getISBN()) + 1);

    char *resultIsbn = new char[resultISBNLength];
    resultFile.read(resultIsbn, resultISBNLength);
    ASSERT_STREQ(resultIsbn, book->getISBN());
    delete[] resultIsbn;

    unsigned int resultFilenameLength;
    resultFile.read((char *) &resultFilenameLength, sizeof(resultFilenameLength));
    ASSERT_EQ(resultFilenameLength, strlen(book->getFilename()) + 1);

    char *resultFilename = new char[resultFilenameLength];
    resultFile.read(resultFilename, resultFilenameLength);
    ASSERT_STREQ(resultFilename, book->getFilename());
    delete[] resultFilename;

    // Verify no additional data is written to the binary file
    ASSERT_TRUE(resultFile.peek() == EOF);

    resultFile.close();
}
