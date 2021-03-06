//
// Created by apenchev on 5/12/2022.
//

#ifndef LIBRARITY_BUT_DUMBER_PROGRAM_H
#define LIBRARITY_BUT_DUMBER_PROGRAM_H

#include <iostream>
#include <cstring>
#include "../library/Library.h"
#include "../helpers/WritingMode.h"
#include "../helpers/PasswordHelper.h"
#include "../exception/BookException.h"
#include "../exception/Exception.h"
#include "../exception/LibraryException.h"

#define MAX_PWD_ATTEMPTS 3
#define MAX_CMD_LEN 32
#define MAX_STR_LEN 1024
#define MAX_LINE_LEN 8196

class Program {
private:
    static void addUserCommand(Library& library, bool isAdministrator);

    static void changePasswordCommand(Library& library, const char* username);

    static void addBookCommand(Library& library, bool isAdministrator);

    static void removeBookCommand(Library& library, bool isAdministrator);

    static void viewCommand(const Library& library);

    static void sortCommand(Library& library);

    static void findCommand(const Library& library);

    static void printCommand(const Library& library);
public:
    static int run();
};


#endif //LIBRARITY_BUT_DUMBER_PROGRAM_H
