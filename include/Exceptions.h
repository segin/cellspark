#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class TermuxApiException : public std::runtime_error {
public:
    explicit TermuxApiException(const std::string& message)
        : std::runtime_error(message) {}
};

class JsonParseException : public std::runtime_error {
public:
    explicit JsonParseException(const std::string& message)
        : std::runtime_error(message) {}
};

#endif // EXCEPTIONS_H
