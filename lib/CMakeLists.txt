project(librarity_but_dumber)

set(HEADER_FILES
        book/Book.h
        user/User.h
        library/Library.h
        enums/ReadingMode.h
        librarity-but-dumber/LibrarityButDumber.h
        )

set(SOURCE_FILES
        book/Book.cpp
        user/User.cpp
        library/Library.cpp
        librarity-but-dumber/LibrarityButDumber.cpp
        )

add_library(librarity_but_dumber_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})