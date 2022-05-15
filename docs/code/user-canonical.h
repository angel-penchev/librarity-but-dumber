class User {
private:
...
public:
    explicit User(const char *username = "", const char *password = "", bool isAdmin = false);

    User(const User &other);

    virtual ~User();
    ...
};