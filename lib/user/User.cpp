//
// Created by apenchev on 5/4/2022.
//

#include "../../include/user/User.h"

User::User(const char *username, const char *password, bool isAdmin)
        : username(), passwordHash(), isAdmin(isAdmin) {
    setUsername(username);
    setPassword(password);
}

User::User(const User &other) : username(), passwordHash(), isAdmin() {
    this->copy(other);
}

User::User(std::istream &in) : username(), passwordHash(), isAdmin() {
    unsigned int usernameLength;
    in.read((char *) &usernameLength, sizeof(usernameLength));
    this->username = new char[usernameLength];
    in.read(this->username, usernameLength);

    unsigned int passwordHashLength;
    in.read((char *) &passwordHashLength, sizeof(passwordHashLength));
    this->passwordHash = new char[passwordHashLength];
    in.read(this->passwordHash, passwordHashLength);

    in.read((char *) &this->isAdmin, sizeof(this->isAdmin));
}

User &User::operator=(const User &other) {
    if (this != &other) {
        this->clear();
        this->copy(other);
    }
    return *this;
}

User::~User() {
    this->clear();
}

std::ofstream &operator<<(std::ofstream &out, const User& user) {
    unsigned int usernameLength = std::strlen(user.username) + 1;
    out.write((const char *) &usernameLength, sizeof(usernameLength));
    out.write((const char *) user.username, usernameLength);

    unsigned int passwordHashLength = std::strlen(user.passwordHash) + 1;
    out.write((const char *) &passwordHashLength, sizeof(passwordHashLength));
    out.write((const char *) user.passwordHash, passwordHashLength);

    out.write((const char *) &user.isAdmin, sizeof(user.isAdmin));

    return out;
}

bool User::verifyPassword(const char *password) {
    const char *encryptedPassword = encryptPassword(password);
    return !std::strcmp(encryptedPassword, this->passwordHash);
}

char *User::getUsername() const {
    return this->username;
}

void User::setUsername(const char *newUsername) {
    if (newUsername == nullptr) {
        return;
    }

    this->username = new char[std::strlen(newUsername) + 1];
    std::strncpy(this->username, newUsername, std::strlen(newUsername) + 1);
}

void User::setPassword(const char *newPassword, bool isEncrypted) {
    if (newPassword == nullptr) {
        return;
    }

    const char *encryptedPassword = !isEncrypted ? encryptPassword(newPassword) : newPassword;

    this->passwordHash = new char[std::strlen(encryptedPassword) + 1];
    std::strncpy(this->passwordHash, encryptedPassword, std::strlen(encryptedPassword) + 1);
}

char *User::getPasswordHash() const {
    return this->passwordHash;
}

bool User::isAdministrator() const {
    return this->isAdmin;
}

void User::setIsAdministrator(bool newIsAdmin) {
    this->isAdmin = newIsAdmin;
}

const char *User::encryptPassword(const char *unencryptedPassword) {
    return unencryptedPassword; //TODO: actually do some encryption
}

void User::copy(const User &other) {
    this->setUsername(other.getUsername());
    this->setPassword(other.getPasswordHash(), true);
    this->setIsAdministrator(other.isAdministrator());
}

void User::clear() {
    delete[] this->username;
    this->username = nullptr;

    delete[] this->passwordHash;
    this->passwordHash = nullptr;
}
