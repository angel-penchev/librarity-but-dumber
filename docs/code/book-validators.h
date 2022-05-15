class Book {
private:
    ...
public:
    ...
    static void validateRating(double newRating);

    static void validateISBN(const char *newISBN);

    static bool isValidRating(double newRating);

    static bool isValidISBN(const char *newISBN);
};