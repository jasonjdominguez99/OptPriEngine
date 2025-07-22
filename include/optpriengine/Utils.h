#pragma once

#include "Error.h"

#include <chrono>

namespace optpriengine::Utils
{

[[nodiscard]] std::expected<double, Error> yearsBetween(const std::chrono::year_month_day& start, const std::chrono::year_month_day& end) noexcept;

} // namespace optpriengine::Utils
