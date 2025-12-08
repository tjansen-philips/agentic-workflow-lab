#ifndef REPOSITORY_EXCEPTIONS_H
#define REPOSITORY_EXCEPTIONS_H

#include <stdexcept>
#include <string>

/**
 * Base exception class for repository errors
 */
class RepositoryException : public std::runtime_error {
public:
    explicit RepositoryException(const std::string& message)
        : std::runtime_error(message) {}
};

/**
 * Exception thrown when JSON parsing fails
 */
class JsonParseException : public RepositoryException {
public:
    explicit JsonParseException(const std::string& message)
        : RepositoryException("JSON parsing error: " + message) {}
};

/**
 * Exception thrown when file I/O operations fail
 */
class FileIOException : public RepositoryException {
public:
    explicit FileIOException(const std::string& message)
        : RepositoryException("File I/O error: " + message) {}
};

#endif // REPOSITORY_EXCEPTIONS_H
