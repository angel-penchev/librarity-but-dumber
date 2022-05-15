/**
 * Attempt to login a user with username and password credentials.
 * @param username Username to attempt login with
 * @param password Password to attempt login with
 * @return Pointer to the user on successful login, otherwise nullptr
 */
User *Library::loginUser(const char *username, const char *password) const {
    // Find the user by username
    int userIndex = this->findUserIndex(username);

    // If the user is not found or if the password is incorrect, return nullptr
    if (userIndex < 0 || !this->users[userIndex].verifyPassword(password)) {
        return nullptr;
    }

    // Return the user if login credentials are correct
    return &this->users[userIndex];
}

/**
 * Change user password.
 * @param username User username
 * @param oldPassword Old user password
 * @param newPassword New password to be set
 * @param newPasswordConfirm Confirmation of the new password
 */
void Library::changeUserPassword(const char *username, const char *oldPassword, const char *newPassword,
                                 const char *newPasswordConfirm) const {
    // Find the user by username
    int userIndex = this->findUserIndex(username);
    if (userIndex < 0) {
        throw LibraryException(LibraryErrorCode::BOOK_NOT_FOUNT_ERR);

    }

    // Verifying the old password matches the one stored
    if (!this->users[userIndex].verifyPassword(oldPassword)) {
        throw LibraryException(LibraryErrorCode::INVALID_OLD_PASSWORD);
    }

    // Verifying the new password and its confirmation match
    if (std::strcmp(newPassword, newPasswordConfirm) != 0) {
        throw LibraryException(LibraryErrorCode::MISMATCHING_PASSWORDS_ERR);
    }

    // Change the password
    this->users[userIndex].setPassword(newPassword);

    // Update users file after the change
    this->updateUsersFile();
}