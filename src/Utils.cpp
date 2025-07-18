#include "Utils.h"

double Utils::yearsBetween(const std::chrono::year_month_day& start, const std::chrono::year_month_day& end)
{
    auto startDays = std::chrono::sys_days(start);
    auto endDays = std::chrono::sys_days(end);

    // TODO: handle start > end case

    return (endDays - startDays).count() / 365.25; // TODO: use a more precise calendar calculation
}