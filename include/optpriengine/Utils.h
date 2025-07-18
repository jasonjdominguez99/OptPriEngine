#pragma once

#include <chrono>

namespace Utils
{
    [[nodiscard]] double yearsBetween(const std::chrono::year_month_day& start, const std::chrono::year_month_day& end) noexcept;
}
