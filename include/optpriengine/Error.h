#pragma once

#include <expected>
#include <string>

enum class ErrorCode
{
    InvalidDateRange = 1
};

struct Error
{
    ErrorCode code;
    std::string message;
    
    explicit Error(ErrorCode errorCode, std::string msg) : code(errorCode), message("Error: " + std::move(msg)) {}
};
