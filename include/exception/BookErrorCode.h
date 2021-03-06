//
// Created by apenchev on 5/13/2022.
//

#ifndef LIBRARITY_BUT_DUMBER_BOOKERRORCODE_H
#define LIBRARITY_BUT_DUMBER_BOOKERRORCODE_H

#include <iostream>

enum BookErrorCode {
    CONTENTS_FILE_READING_ERR,
    CONTENTS_FILE_WRITING_ERR,
    CONTENTS_FILE_REMOVAL_ERR,
    INVALID_RATING_RANGE,
    INVALID_ISBN_LENGTH,
    INVALID_ISBN_GS1_PREFIX,
    INVALID_ISBN_CHARACTERS,
    INVALID_ISBN_CHECKSUM_CHARACTER,
    INVALID_ISBN_CHECKSUM,
};

#endif //LIBRARITY_BUT_DUMBER_BOOKERRORCODE_H
