//
// Created by apenchev on 5/13/2022.
//

#ifndef LIBRARITY_BUT_DUMBER_PASSWORDHELPER_H
#define LIBRARITY_BUT_DUMBER_PASSWORDHELPER_H


#include <iostream>

class PasswordHelper {
private:
    static void enableInputEcho(bool on);

public:
    static void inputPassword(char *passwordBuffer, unsigned int length, bool printNewLine = true);
};


#endif //LIBRARITY_BUT_DUMBER_PASSWORDHELPER_H
