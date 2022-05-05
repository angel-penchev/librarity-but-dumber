//
// Created by apenchev on 5/4/2022.
//

#include <cstring>
#include "User.h"

User::User(char *username, char *password) : username(), passwordHash() {
    setUsername(username);
    setPassword(password);
}

User::User(const User &other) {
    this->copy(other);
}

User &User::operator=(const User& other) {
    if (this != &other) {
        this->clear();
        this->copy(other);
    }
    return *this;
}

User::~User() {
    this->clear();
}

char *User::getUsername() const {
    return this->username;
}

void User::setUsername(char *newUsername) {
    if (newUsername == nullptr) {
        return;
    }

    delete[] this->username;
    this->username = new char[std::strlen(newUsername) + 1];
    std::strncpy(this->username, newUsername, std::strlen(newUsername) + 1);
}

void User::setPassword(char *newPassword, bool isEncrypted) {
    if (newPassword == nullptr) {
        return;
    }

    char *encryptedPassword = isEncrypted ? encryptPassword(newPassword) : newPassword;

    delete[] this->passwordHash;
    this->passwordHash = new char[std::strlen(encryptedPassword) + 1];
    std::strncpy(this->passwordHash, encryptedPassword, std::strlen(encryptedPassword) + 1);
}

char *User::getPasswordHash() const {
    return this->passwordHash;
}

char *User::encryptPassword(char *unencryptedPassword) {
    return unencryptedPassword; //TODO: actually do some encryption
}

void User::copy(const User &other) {
    this->setUsername(other.getUsername());
    this->setPassword(other.getPasswordHash(), true);
}

void User::clear() {
    delete[] this->username;
    this->username = nullptr;

    delete[] this->passwordHash;
    this->passwordHash = nullptr;
}
