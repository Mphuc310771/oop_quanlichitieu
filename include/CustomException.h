#pragma once
#include <exception>
#include <string>

// Minh họa tính kế thừa: FileException kế thừa từ std::exception
class FileException : public std::exception {
private:
    std::string message;
public:
    FileException(const std::string& msg) : message(msg) {}

    // Minh họa tính đa hình: Ghi đè phương thức virtual what()
    const char* what() const noexcept override {
        return message.c_str();
    }
};
