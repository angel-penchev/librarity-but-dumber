class User {
private:
    ...

public:
    ...

    char *getUsername() const;

    void setUsername(const char *newUsername);

    void setPassword(const char *newPassword, bool isEncrypted = false);

    bool isAdministrator() const;

    void setIsAdministrator(bool newIsAdmin);
};