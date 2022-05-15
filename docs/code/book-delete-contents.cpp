/**
 * Deletes the book contents file
 */
void Book::deleteBookContents() const {
    // Remove contents file
    if (remove(this->filename)) {
        throw BookException(BookErrorCode::CONTENTS_FILE_REMOVAL_ERR);
    }
}