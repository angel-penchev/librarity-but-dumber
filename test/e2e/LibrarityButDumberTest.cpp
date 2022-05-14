//
// Created by apenchev on 5/11/2022.
//

#include "gtest/gtest.h"
#include "../../include/program/Program.h"

class LibrarityButDumberFixture : public ::testing::Test {
protected:
    std::stringstream inputStream;
    std::stringstream outputStream;
    std::stringstream errorStream;

    void SetUp() override {
        // Redirect cin, cout and cerr to stringstreams
        std::cin.rdbuf(inputStream.rdbuf());
        std::cout.rdbuf(outputStream.rdbuf());
        std::cerr.rdbuf(errorStream.rdbuf());
    }

    void TearDown() override {
        // Delete created files
        remove("books.bin");
        remove("users.bin");

        // Reset streams
        inputStream.str("");
        outputStream.str("");
        errorStream.str("");
    }
};

TEST_F(LibrarityButDumberFixture, ShouldAcceptDefaultLoginCredentials) {
    std::stringstream expectedOutputStream;
    std::stringstream expectedErrorStream;

    // Login with default credentials
    // Requesting username
    expectedOutputStream << "Username: ";
    inputStream << "admin\n";

    // Requesting password
    expectedOutputStream << "Password: ";
    inputStream << "admin\n";
    expectedOutputStream << "\n";

    // Expecting no error thrown, just regular prompt indicator
    expectedOutputStream << "|> ";

    // Expect a new line before program ending
    expectedOutputStream << "\n";

    // Running the program
    Program::run();

    // Asserting if expected output equals actual
    ASSERT_TRUE(outputStream.str() == expectedOutputStream.str());
    ASSERT_TRUE(errorStream.str() == expectedErrorStream.str());

    // Verify the users binary has only 1 user - the administrator
    std::ifstream usersFile("users.bin", std::ios::binary | std::ios::in);
    ASSERT_TRUE(usersFile);

    unsigned int usersCountFromFile;
    usersFile.read((char *) &usersCountFromFile, sizeof(usersCountFromFile));
    ASSERT_EQ(usersCountFromFile, 1);

    User user = User(usersFile);
    ASSERT_STREQ(user.getUsername(), "admin");
    ASSERT_TRUE(user.isAdministrator());

    usersFile.close();
}

TEST_F(LibrarityButDumberFixture, ShouldExitOn3InvalidPassords) {
    std::stringstream expectedOutputStream;
    std::stringstream expectedErrorStream;

    // Login with invalid credentials
    // Requesting username
    expectedOutputStream << "Username: ";
    inputStream << "admin\n";

    // Inputting 3 invalid passwords
    expectedOutputStream << "Password: ";
    inputStream << "gosho\n";
    expectedErrorStream << "WARN: Invalid password! You have 2 attempts left.\n";
    expectedOutputStream << "\n";

    expectedOutputStream << "Password: ";
    inputStream << "losho\n";
    expectedErrorStream << "WARN: Invalid password! You have 1 attempts left.\n";
    expectedOutputStream << "\n";

    expectedOutputStream << "Password: ";
    inputStream << "posho\n";
    expectedErrorStream << "WARN: Invalid password! You have 0 attempts left.\n";
    expectedOutputStream << "\n";

    // Expecting an authentication error message
    expectedErrorStream << "ERR: Failed to authenticate user!\n";

    // Running the program
    Program::run();

    // Asserting if expected output equals actual
    ASSERT_TRUE(outputStream.str() == expectedOutputStream.str());
    ASSERT_TRUE(errorStream.str() == expectedErrorStream.str());
}

TEST_F(LibrarityButDumberFixture, ShouldLetAdministratorAddNewUsersToBinaryFile) {
    std::stringstream expectedOutputStream;
    std::stringstream expectedErrorStream;

    // Authenticate with default credentials
    expectedOutputStream << "Username: ";
    inputStream << "admin\n";
    expectedOutputStream << "Password: ";
    inputStream << "admin\n";
    expectedOutputStream << "\n|> ";

    // Create a new user command
    inputStream << "add user\n";

    // Username input for new user
    expectedOutputStream << "|-> Username: ";
    inputStream << "gosho\n";

    // Password input for new user
    expectedOutputStream << "|-> Password: ";
    inputStream << "veristr0nkandsecurpa$$w0rd\n";
    expectedOutputStream << "\n";

    // Is the new user administrator
    expectedOutputStream << "|-> Is administrator (y/n): ";
    inputStream << "n\n";

    // Expecting no error thrown, just regular prompt indicator
    expectedOutputStream << "|> ";

    // Expect a new line before program ending
    expectedOutputStream << "\n";

    // Running the program
    Program::run();

    // Asserting if expected output equals actual
    ASSERT_TRUE(outputStream.str() == expectedOutputStream.str());
    ASSERT_TRUE(errorStream.str() == expectedErrorStream.str());

    // Verify the users binary has 2 admin - the administrator, and the new admin
    std::ifstream usersFile("users.bin", std::ios::binary | std::ios::in);
    ASSERT_TRUE(usersFile);

    unsigned int usersCountFromFile;
    usersFile.read((char *) &usersCountFromFile, sizeof(usersCountFromFile));
    ASSERT_EQ(usersCountFromFile, 2);

    User admin = User(usersFile);
    ASSERT_STREQ(admin.getUsername(), "admin");
    ASSERT_TRUE(admin.isAdministrator());

    User newUser = User(usersFile);
    ASSERT_STREQ(newUser.getUsername(), "gosho");
    ASSERT_FALSE(newUser.isAdministrator());

    usersFile.close();

    // Reset stringstreams for new program execution
    std::stringstream inputStream2;
    std::cin.rdbuf(inputStream2.rdbuf());
    outputStream.str("");
    errorStream.str("");
    expectedOutputStream.str("");
    expectedErrorStream.str("");

    // Authenticate with new user credentials
    expectedOutputStream << "Username: ";
    inputStream2 << "gosho\n";
    expectedOutputStream << "Password: ";
    inputStream2 << "veristr0nkandsecurpa$$w0rd\n";
    expectedOutputStream << "\n";

    // Expecting no error thrown, just regular prompt indicator
    expectedOutputStream << "|> ";

    // Trying to add new user from non-administrator account - should fail with error
    inputStream2 << "add user\n";
    expectedErrorStream << "ERR: Admin privileges required!\n";
    expectedOutputStream << "|> ";

    // Expect a new line before program ending
    expectedOutputStream << "\n";

    // Running the program
    Program::run();

    // Asserting if expected output equals actual
    ASSERT_TRUE(outputStream.str() == expectedOutputStream.str());
    ASSERT_TRUE(errorStream.str() == expectedErrorStream.str());
}

TEST_F(LibrarityButDumberFixture, ShouldLetUserChangePassword) {
    std::stringstream expectedOutputStream;
    std::stringstream expectedErrorStream;

    // Authenticate with default credentials
    expectedOutputStream << "Username: ";
    inputStream << "admin\n";
    expectedOutputStream << "Password: ";
    inputStream << "admin\n";
    expectedOutputStream << "\n|> ";

    // Change password command
    inputStream << "change password\n";

    // Inputs for password change
    expectedOutputStream << "|-> Old password: ";
    inputStream << "admin\n";
    expectedOutputStream << "\n";
    expectedOutputStream << "|-> New password: ";
    inputStream << "veristr0nkandsecurpa$$w0rd\n";
    expectedOutputStream << "\n";
    expectedOutputStream << "|-> New password (confirm): ";
    inputStream << "veristr0nkandsecurpa$$w0rd\n";
    expectedOutputStream << "\n";

    // Expecting no error thrown, just regular prompt indicator
    expectedOutputStream << "|> ";

    // Expect a new line before program ending
    expectedOutputStream << "\n";

    // Running the program
    Program::run();

    // Asserting if expected output equals actual
    ASSERT_TRUE(outputStream.str() == expectedOutputStream.str());
    ASSERT_TRUE(errorStream.str() == expectedErrorStream.str());

    // Reset stringstreams for new program execution
    std::stringstream inputStream2;
    std::cin.rdbuf(inputStream2.rdbuf());
    outputStream.str("");
    errorStream.str("");
    expectedOutputStream.str("");
    expectedErrorStream.str("");

    // Authenticate with new user credentials
    expectedOutputStream << "Username: ";
    inputStream2 << "admin\n";
    expectedOutputStream << "Password: ";
    inputStream2 << "veristr0nkandsecurpa$$w0rd\n";
    expectedOutputStream << "\n";

    // Expecting no error thrown, just regular prompt indicator
    expectedOutputStream << "|> ";

    // Expect a new line before program ending
    expectedOutputStream << "\n";

    // Running the program
    Program::run();

    // Asserting if expected output equals actual
    ASSERT_TRUE(outputStream.str() == expectedOutputStream.str());
    ASSERT_TRUE(errorStream.str() == expectedErrorStream.str());
}
