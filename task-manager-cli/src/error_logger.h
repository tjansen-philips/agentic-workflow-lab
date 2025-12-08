#ifndef ERROR_LOGGER_H
#define ERROR_LOGGER_H

#include <string>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

/**
 * Utility class for logging errors to stderr with timestamps
 */
class ErrorLogger {
public:
    /**
     * Log an error message to stderr with timestamp
     * @param context The context or operation where the error occurred
     * @param message The error message
     */
    static void logError(const std::string& context, const std::string& message) {
        std::cerr << "[" << getCurrentTimestamp() << "] ERROR [" << context << "]: " 
                  << message << std::endl;
    }

private:
    /**
     * Get current timestamp as a formatted string
     * @return Timestamp string in format: YYYY-MM-DD HH:MM:SS
     */
    static std::string getCurrentTimestamp() {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
};

#endif // ERROR_LOGGER_H
