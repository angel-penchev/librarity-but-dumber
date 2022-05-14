//
// Created by apenchev on 5/15/2022.
//

#include <iostream>
#include "../../include/helpers/StringHelper.h"

const char *StringHelper::toLowercase(const char *string) {
    unsigned int length = std::strlen(string);
    char *result = new char [length + 1];

    for (unsigned int i = 0; i < length; i++) {
        result[i] = (char) std::tolower(string[i]);
    }
    result[length] = '\0';

    return result;
}
