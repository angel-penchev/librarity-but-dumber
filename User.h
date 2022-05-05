//
// Created by apenchev on 5/4/2022.
//

#ifndef LIBRARITY_BUT_DUMBER_USER_H
#define LIBRARITY_BUT_DUMBER_USER_H


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

    User& operator=(const User& other);

    virtual ~User();

    char *getUsername() const;

    void setUsername(char *newUsername);

    void setPassword(char *newPassword, bool isEncrypted = false);

};


#endif //LIBRARITY_BUT_DUMBER_USER_H
