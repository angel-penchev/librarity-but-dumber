project(librarity_but_dumber)

set(HEADER_FILES
        book/Book.h
        book/BookException.h
        user/User.h
        library/Library.h
        enums/ReadingMode.h
        enums/WritingMode.h
        enums/BookErrorCode.h
        helpers/PasswordHelper.h
        librarity-but-dumber/LibrarityButDumber.h
        )

set(SOURCE_FILES
        book/Book.cpp
        book/BookException.cpp
        user/User.cpp
        library/Library.cpp
        helpers/PasswordHelper.cpp
        librarity-but-dumber/LibrarityButDumber.cpp
        )

add_library(librarity_but_dumber_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})