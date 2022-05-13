//
// Created by apenchev on 5/13/2022.
//

#ifndef LIBRARITY_BUT_DUMBER_BOOKEXCEPTION_H
#define LIBRARITY_BUT_DUMBER_BOOKEXCEPTION_H


#include <exception>
#include "enums/BookErrorCode.h"

class BookException : public std::exception {
private:
    BookErrorCode errorCode;

public:
    BookException(BookErrorCode errorCode);

    BookErrorCode getErrorCode() const;

    const char *getErrorMessage() const;
};


#endif //LIBRARITY_BUT_DUMBER_BOOKEXCEPTION_H
