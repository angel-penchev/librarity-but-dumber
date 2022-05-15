/**
 * Verifies whether an input password matches the one User has.
 * @param password Password to be checked
 * @return Whether the passwords match or not
 */
bool User::verifyPassword(const char *password) {
    const char *encryptedPassword = encryptPassword(password);
    return !std::strcmp(encryptedPassword, this->passwordHash);
}