//
// Created by apenchev on 5/13/2022.
//

#ifndef LIBRARITY_BUT_DUMBER_BOOKEXCEPTION_H
#define LIBRARITY_BUT_DUMBER_BOOKEXCEPTION_H


#include "BookErrorCode.h"
#include "Exception.h"

class BookException : public Exception<BookErrorCode> {
public:
    explicit BookException(BookErrorCode errorCode);

    const char *getErrorMessage() const override;
};


#endif //LIBRARITY_BUT_DUMBER_BOOKEXCEPTION_H
