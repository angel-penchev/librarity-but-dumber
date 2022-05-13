//
// Created by apenchev on 5/13/2022.
//

#ifndef LIBRARITY_BUT_DUMBER_LIBRARYEXCEPTION_H
#define LIBRARITY_BUT_DUMBER_LIBRARYEXCEPTION_H


#include <exception>
#include "enums/LibraryErrorCode.h"

class LibraryException : public std::exception {
private:
    LibraryErrorCode errorCode;
public:
    LibraryException(LibraryErrorCode errorCode);

    LibraryErrorCode getErrorCode() const;

    const char *getErrorMessage() const;
};


#endif //LIBRARITY_BUT_DUMBER_LIBRARYEXCEPTION_H
