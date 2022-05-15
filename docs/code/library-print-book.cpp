/**
 * Prints the contents of a book.
 * @param book Book whose contents to be printed
 * @param readingMode Whether to print the entire book at once, with page separation or with sentence separation.
 * @param linesCount Lines in a book page
 */
void Library::printBookContent(Book *book, ReadingMode readingMode, unsigned int linesCount) {
    switch (readingMode) {
        case ReadingMode::WHOLE_BOOK:
            book->printAllContents();
            break;
        case ReadingMode::PAGES:
            book->printPaginatedContents(linesCount);
            break;
        case ReadingMode::SENTENCES:
            book->printSentenceSeparatedContents();
            break;
        default:
            throw std::invalid_argument("Unimplemented item");
    }
}