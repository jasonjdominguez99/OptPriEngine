#pragma once

#include "Error.h"

#include <chrono>

namespace Utils
{
    [[nodiscard]] std::expected<double, Error> yearsBetween(const std::chrono::year_month_day& start, const std::chrono::year_month_day& end) noexcept;
}
