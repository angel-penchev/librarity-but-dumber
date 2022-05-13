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
        case LibraryErrorCode::DUPLICATE_ISBN:
            return "A book with the same ISBN already exists!";
        case LibraryErrorCode::DUPLICATE_USERNAME:
            return "A user with the same username already exists!";
        case LibraryErrorCode::INVALID_OLD_PASSWORD:
            return "Invalid old password!";
        case LibraryErrorCode::MISMATCHING_PASSWORDS_ERR:
            return "New passwords don't match!";
        case LibraryErrorCode::BOOK_NOT_FOUNT_ERR:
            return "Book not found!";
        default:
            throw std::invalid_argument("Unimplemented item");
    }
}
