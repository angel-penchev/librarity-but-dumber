class Book {
    ...
public:
    ...
    char *getName() const;

    void setName(const char *newName);

    char *getAuthor() const;

    void setAuthor(const char *newAuthor);

    char *getDescription() const;

    void setDescription(const char *newDescription);

    double getRating() const;

    void setRating(double newRating);

    char *getISBN() const;

    void setISBN(const char *newISBN);

    char *getFilename() const;

    void setFilename(const char *newFilename);
    ...
};
