set(LIBRARY_NAME librarity_but_dumber_lib)

project(${LIBRARY_NAME})

set(HEADERS_DIR ../include)

set(HEADER_FILES
        ${HEADERS_DIR}/book/Book.h
        ${HEADERS_DIR}/user/User.h
        ${HEADERS_DIR}/library/Library.h
        ${HEADERS_DIR}/helpers/ReadingMode.h
        ${HEADERS_DIR}/helpers/WritingMode.h
        ${HEADERS_DIR}/helpers/SortingMode.h
        ${HEADERS_DIR}/helpers/FindMode.h
        ${HEADERS_DIR}/helpers/PasswordHelper.h
        ${HEADERS_DIR}/helpers/StringHelper.h
        ${HEADERS_DIR}/exception/BookErrorCode.h
        ${HEADERS_DIR}/exception/LibraryErrorCode.h
        ${HEADERS_DIR}/exception/BookException.h
        ${HEADERS_DIR}/exception/LibraryException.h
        ${HEADERS_DIR}/program/Program.h)

set(SOURCE_FILES
        book/Book.cpp
        user/User.cpp
        library/Library.cpp
        helpers/PasswordHelper.cpp
        helpers/StringHelper.cpp
        exception/BookException.cpp
        exception/LibraryException.cpp
        program/Program.cpp helpers/StringHelper.cpp)

add_library(${LIBRARY_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})
