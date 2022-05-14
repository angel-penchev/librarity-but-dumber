//
// Created by apenchev on 5/13/2022.
//

#ifndef LIBRARITY_BUT_DUMBER_LIBRARYEXCEPTION_H
#define LIBRARITY_BUT_DUMBER_LIBRARYEXCEPTION_H


#include <exception>
#include <stdexcept>
#include "LibraryErrorCode.h"
#include "Exception.h"

class LibraryException : public Exception<LibraryErrorCode> {
public:
    explicit LibraryException(LibraryErrorCode errorCode);

    const char *getErrorMessage() const override;
};


#endif //LIBRARITY_BUT_DUMBER_LIBRARYEXCEPTION_H
