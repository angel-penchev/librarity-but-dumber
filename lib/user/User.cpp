//
// Created by apenchev on 5/4/2022.
//

#include "../../include/user/User.h"

/**
 * User parameter constructor.
 * @param username User login username
 * @param password User login password
 * @param isAdmin Weather the user is administrator or not
 */
User::User(const char *username, const char *password, bool isAdmin)
        : username(), passwordHash(), isAdmin(isAdmin) {
    setUsername(username);
    setPassword(password);
}

/**
 * User copy-constructor.
 * @param other Reference to another User object
 */
User::User(const User &other) : username(), passwordHash(), isAdmin() {
    this->copy(other);
}

/**
 * User file constructor.
 * Reads the information for a user from a file stream and constructs a User object based on it.
 * @param in Input file stream
 */
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

/**
 * Equality "=" operator override.
 * @param other Reference to another User object
 * @return Reference to self
 */
User &User::operator=(const User &other) {
    if (this != &other) {
        this->clear();
        this->copy(other);
    }
    return *this;
}

/**
 * Output "<<" operator override for output file streams.
 * Serializes the information of a User in a binary output file.
 * @param out Output file stream
 * @param book Reference to a Book object to output
 * @return
 */
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

/**
 * User destructor.
 */
User::~User() {
    this->clear();
}

/**
 * Verifies whether an input password matches the one User has.
 * @param password Password to be checked
 * @return Whether the passwords match or not
 */
bool User::verifyPassword(const char *password) {
    const char *encryptedPassword = encryptPassword(password);
    return !std::strcmp(encryptedPassword, this->passwordHash);
}

/**
 * User username getter.
 * @return User username
 */
char *User::getUsername() const {
    return this->username;
}

/**
 * User username setter.
 * @param newUsername Username to be set
 */
void User::setUsername(const char *newUsername) {
    // Verifying input is not null
    if (newUsername == nullptr) {
        return;
    }

    // Allocating memory and copying the input username
    this->username = new char[std::strlen(newUsername) + 1];
    std::strncpy(this->username, newUsername, std::strlen(newUsername) + 1);
}

/**
 * Password hash getter.
 * @return Hashed version of User password
 */
char *User::getPasswordHash() const {
    return this->passwordHash;
}

/**
 * User password setter.
 * @param newPassword New password to be set
 * @param isEncrypted Whether the input password is encrypted or not
 */
void User::setPassword(const char *newPassword, bool isEncrypted) {
    // Verifying input is not null
    if (newPassword == nullptr) {
        return;
    }

    // Encrypts the password if it is not encrypted already
    const char *encryptedPassword = !isEncrypted ? encryptPassword(newPassword) : newPassword;

    // Allocating memory and copying the input encrypted password
    this->passwordHash = new char[std::strlen(encryptedPassword) + 1];
    std::strncpy(this->passwordHash, encryptedPassword, std::strlen(encryptedPassword) + 1);
}

/**
 * User isAdmin getter.
 * @return Whether the user is administrator or not
 */
bool User::isAdministrator() const {
    return this->isAdmin;
}

/**
 * User isAdmin setter.
 * @param newIsAdmin Administrator value to be set
 */
void User::setIsAdministrator(bool newIsAdmin) {
    this->isAdmin = newIsAdmin;
}

/**
 * Encrypts an input password.
 * @param unencryptedPassword Password to be encrypted
 * @return Encrypted version of the password
 */
const char *User::encryptPassword(const char *unencryptedPassword) {
    return unencryptedPassword; //TODO: actually do some encryption
}

/**
 * Sets object properties from another User object.
 * @param other Reference to another User object
 */
void User::copy(const User &other) {
    this->setUsername(other.getUsername());
    this->setPassword(other.getPasswordHash(), true);
    this->setIsAdministrator(other.isAdministrator());
}

/**
 * Frees dynamically allocated object memory.
 */
void User::clear() {
    delete[] this->username;
    this->username = nullptr;

    delete[] this->passwordHash;
    this->passwordHash = nullptr;
}
