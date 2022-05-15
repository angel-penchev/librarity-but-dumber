/**
 * Sort books by criteria.
 * @param sortingMode
 */
void Library::sortBooks(SortingMode sortingMode) {
    for (int i = 0; i < (int) this->booksCount - 1; i++) {
        for (int j = i + 1; j < (int) this->booksCount; j++) {
            bool swapCondition;
            switch (sortingMode) {
                case SortingMode::SORT_BY_NAME:
                    swapCondition = std::strcmp(this->books[i].getName(), this->books[j].getName()) > 0;
                    break;
                case SortingMode::SORT_BY_AUTHOR:
                    swapCondition = std::strcmp(this->books[i].getAuthor(), this->books[j].getAuthor()) > 0;
                    break;
                case SortingMode::SORT_BY_RATING:
                    swapCondition = this->books[i].getRating() > this->books[j].getRating();
                    break;
            }

            if (swapCondition) {
                Book tempBook = books[i];
                this->books[i] = this->books[j];
                this->books[j] = tempBook;
            }
        }
    }
}