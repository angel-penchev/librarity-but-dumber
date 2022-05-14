//
// Created by apenchev on 5/13/2022.
//

#include "../../include/exception/BookException.h"

BookException::BookException(BookErrorCode errorCode) : Exception(errorCode) {}

const char *BookException::getErrorMessage() const {
    switch (this->errorCode) {
        case CONTENTS_FILE_READING_ERR:
            return "Book content file could not be opened for reading!";
        case CONTENTS_FILE_WRITING_ERR:
            return "Book content file could not be opened for writing!";
        case INVALID_RATING_RANGE:
            return "Invalid rating! Rating should be between 0.0 and 10.0.";
        case INVALID_ISBN_LENGTH:
            return "Invalid ISBN length!";
        case INVALID_ISBN_GS1_PREFIX:
            return "Invalid ISBN GS1 prefix!";
        case INVALID_ISBN_CHARACTERS:
            return "Invalid characters in ISBN!";
        case INVALID_ISBN_CHECKSUM_CHARACTER:
            return "Invalid ISBN checksum character!";
        case INVALID_ISBN_CHECKSUM:
            return "Invalid ISBN checksum!";
        default:
            throw std::invalid_argument("Unimplemented item");
    }
}
