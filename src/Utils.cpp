#include "Utils.h"

std::expected<double, Error> Utils::yearsBetween(const std::chrono::year_month_day& start, const std::chrono::year_month_day& end) noexcept
{
    if (start > end) {
        return std::unexpected(Error(ErrorCode::InvalidDateRange, std::format("Start date ({}) must be before or equal to end date ({}).", start, end)));
    }

    auto startDays = std::chrono::sys_days(start);
    auto endDays = std::chrono::sys_days(end);

    return (endDays - startDays).count() / 365.25; // TODO: use a more precise calendar calculation
}