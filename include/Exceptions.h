#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

/**
 * @class TermuxApiException
 * @brief Exception for errors related to the Termux API.
 */
class TermuxApiException : public std::runtime_error {
public:
    /**
     * @brief Construct a new TermuxApiException object.
     *
     * @param message The error message.
     */
    explicit TermuxApiException(const std::string& message)
        : std::runtime_error(message) {}
};

/**
 * @class JsonParseException
 * @brief Exception for errors related to JSON parsing.
 */
class JsonParseException : public std::runtime_error {
public:
    /**
     * @brief Construct a new JsonParseException object.
     *
     * @param message The error message.
     */
    explicit JsonParseException(const std::string& message)
        : std::runtime_error(message) {}
};

#endif // EXCEPTIONS_H
