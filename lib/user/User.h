//
// Created by apenchev on 5/4/2022.
//

#ifndef LIBRARITY_BUT_DUMBER_USER_H
#define LIBRARITY_BUT_DUMBER_USER_H


#include <fstream>

class User {
private:
    char *username;
    char *passwordHash;

    char *getPasswordHash() const;

    static const char *encryptPassword(const char *unencryptedPassword);

    void copy(const User &other);

    void clear();

public:
    User(const char *username = "", const char *password = "");

    User(const User &other);

    User(std::istream &in);

    User &operator=(const User &other);

    virtual ~User();

    void serialize(std::ostream &out);

    char *getUsername() const;

    void setUsername(const char *newUsername);

    void setPassword(const char *newPassword, bool isEncrypted = false);

};


#endif //LIBRARITY_BUT_DUMBER_USER_H
