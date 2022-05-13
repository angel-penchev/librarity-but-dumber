//
// Created by apenchev on 5/13/2022.
//

#include <stdexcept>
#include "LibraryException.h"

LibraryException::LibraryException(LibraryErrorCode errorCode) : errorCode(errorCode) {}

LibraryErrorCode LibraryException::getErrorCode() const {
    return errorCode;
}

const char *LibraryException::getErrorMessage() const {
    switch (this->errorCode) {
        case INVALID_OLD_PASSWORD:
            return "Invalid old password!";
        case MISMATCHING_PASSWORDS:
            return "New passwords don't match!";
        case INVALID_READING_MODE:
            return "Invalid reading mode!";
        default:
            throw std::invalid_argument("Unimplemented item");
    }
}
