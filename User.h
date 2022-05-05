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

    static char *encryptPassword(char* unencryptedPassword);

    void copy(const User &other);

    void clear();
public:
    User(char *username, char *password);

    User(const User &other);

    User(std::ifstream& in);

    User& operator=(const User& other);

    virtual ~User();

    void serialize(std::ofstream &out);

    char *getUsername() const;

    void setUsername(char *newUsername);

    void setPassword(char *newPassword, bool isEncrypted = false);

};


#endif //LIBRARITY_BUT_DUMBER_USER_H
