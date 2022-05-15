class Program {
private:
    static void addUserCommand(Library& library, bool isAdministrator);

    static void changePasswordCommand(Library& library, const char* username);

    static void addBookCommand(Library library, bool isAdministrator);

    static void removeBookCommand(Library library, bool isAdministrator);

    static void viewCommand(const Library& library);

    static void sortCommand(Library library);

    static void findCommand(const Library& library);

    static void printCommand(const Library& library);
public:
    static int run();
};