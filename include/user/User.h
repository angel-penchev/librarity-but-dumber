//
// Created by apenchev on 5/4/2022.
//

#ifndef LIBRARITY_BUT_DUMBER_USER_H
#define LIBRARITY_BUT_DUMBER_USER_H

#include <fstream>
#include <cstring>

class User {
private:
    char *username;
    char *passwordHash;
    bool isAdmin;

    char *getPasswordHash() const;

    static const char *encryptPassword(const char *unencryptedPassword);

    void copy(const User &other);

    void clear();

public:
    explicit User(const char *username = "", const char *password = "", bool isAdmin = false);

    User(const User &other);

    explicit User(std::istream &in);

    User &operator=(const User &other);

    friend std::ofstream &operator<<(std::ofstream &out, const User& user);

    virtual ~User();

    bool verifyPassword(const char *password);

    char *getUsername() const;

    void setUsername(const char *newUsername);

    void setPassword(const char *newPassword, bool isEncrypted = false);

    bool isAdministrator() const;

    void setIsAdministrator(bool newIsAdmin);
};


#endif //LIBRARITY_BUT_DUMBER_USER_H
