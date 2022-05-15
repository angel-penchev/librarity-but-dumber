/**
 * Output "<<" operator override for output file streams.
 * Serializes the information of a User in a binary output file.
 * @param out Output file stream
 * @param book Reference to a Book object to output
 * @return
 */
std::ofstream &operator<<(std::ofstream &out, const User& user) {
    unsigned int usernameLength = std::strlen(user.username) + 1;
    out.write((const char *) &usernameLength, sizeof(usernameLength));
    out.write((const char *) user.username, usernameLength);

    unsigned int passwordHashLength = std::strlen(user.passwordHash) + 1;
    out.write((const char *) &passwordHashLength, sizeof(passwordHashLength));
    out.write((const char *) user.passwordHash, passwordHashLength);

    out.write((const char *) &user.isAdmin, sizeof(user.isAdmin));

    return out;
}