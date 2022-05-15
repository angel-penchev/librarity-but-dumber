class Book {
...
public:
    explicit Book(const char *name = "Untitled", const char *author = "Unknown author", const char *description = "",
         double rating = 0, const char *ISBN = "9780000000002", const char *filename = "");

    Book(const Book &other);

    Book &operator=(const Book &other);

    virtual ~Book();

    ...
};