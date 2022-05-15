class Library {
private:
...
public:
    Library();

    Library(const Library &other);

    Library &operator=(const Library &other);

    virtual ~Library();
};
