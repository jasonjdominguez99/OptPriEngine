#pragma once

#include <chrono>
#include <expected>

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

namespace Utils
{
    [[nodiscard]] std::expected<double, Error> yearsBetween(const std::chrono::year_month_day& start, const std::chrono::year_month_day& end) noexcept;
}
