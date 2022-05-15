/**
 * Library parameter constructor.
 * @param booksFilename Filename of the books binary file
 * @param usersFilename Filename of the users binary file
 */
Library::Library(const char *booksFilename, const char *usersFilename) : books(new Book[0]), users(new User[0]),
                                                                         booksFilename(), usersFilename() {
    // Set books and users filename properties
    this->setBooksFilename(booksFilename);
    this->setUsersFilename(usersFilename);

    // Read books from the books binary if it exists
    std::ifstream booksFile(this->booksFilename, std::ios::binary | std::ios::in);
    if (booksFile) {
        unsigned int booksCountFromFile;
        booksFile.read((char *) &booksCountFromFile, sizeof(booksCountFromFile));
        for (unsigned int i = 0; i < booksCountFromFile; i++) {
            this->addBook(Book(booksFile));
        }
    }
    booksFile.close();

    // Try to open users file and read the users from there.
    // If that fails, creating a new users file with a default admin.
    std::ifstream usersFile(usersFilename, std::ios::binary | std::ios::in);
    if (!usersFile) {
        // Add a default administrator to the users
        User defaultAdmin = User("admin", "admin", true);
        this->addUser(defaultAdmin);

        // Create new users file with the administrator
        this->updateUsersFile();
        return;
    }

    // Read users from the books binary
    unsigned int usersCountFromFile;
    usersFile.read((char *) &usersCountFromFile, sizeof(usersCountFromFile));
    for (unsigned int i = 0; i < usersCountFromFile; i++) {
        this->addUser(User(usersFile));
    }
    usersFile.close();
}