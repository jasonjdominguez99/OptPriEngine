#pragma once

#include "OptionStyle.h"
#include "StrategyParameters.h"
#include "Utils.h"

#include <chrono>
#include <expected>

namespace optpriengine
{

struct MarketData
{
    double spotPrice; // Current price of the underlying asset
    double volatility; // Volatility of the underlying asset (% per year)
    double riskFreeInterestRate; // Risk-free interest rate (% per year)
};

template <OptionStyle Style>
class Option
{
public:
    explicit Option(const double strikePrice, const std::chrono::year_month_day& expirationDate) noexcept
        :
        m_strikePrice(strikePrice),
        m_expirationDate(expirationDate) {}

    // Pricing
    template <typename Strategy>
    [[nodiscard]] std::expected<double, Error> callPrice(const MarketData& marketData, const std::chrono::year_month_day& valuationDate) const noexcept
    {
        static_assert(Strategy::supportsOptionStyle(Style), "Pricing strategy does not support the specified option style.");

        const auto yearsToMaturity = Utils::yearsBetween(valuationDate, m_expirationDate);
        if (!yearsToMaturity)
        {
            return yearsToMaturity;
        }

        return Strategy::calculateCallPrice({ m_strikePrice, marketData.spotPrice, marketData.volatility, marketData.riskFreeInterestRate, yearsToMaturity.value() }, Style);
    }

    template <typename Strategy>
    [[nodiscard]] std::expected<double, Error> putPrice(const MarketData& marketData, const std::chrono::year_month_day& valuationDate) const noexcept
    {
        static_assert(Strategy::supportsOptionStyle(Style), "Pricing strategy does not support the specified option style.");

        const auto yearsToMaturity = Utils::yearsBetween(valuationDate, m_expirationDate);
        if (!yearsToMaturity)
        {
            return yearsToMaturity;
        }

        return Strategy::calculatePutPrice({ m_strikePrice, marketData.spotPrice, marketData.volatility, marketData.riskFreeInterestRate, yearsToMaturity.value() }, Style);
    }

    // Greeks
    template <typename Strategy>
    [[nodiscard]] std::expected<double, Error> callDelta(const MarketData& marketData, const std::chrono::year_month_day& valuationDate) const noexcept
    {
        static_assert(Strategy::supportsOptionStyle(Style), "Pricing strategy does not support the specified option style.");

        const auto yearsToMaturity = Utils::yearsBetween(valuationDate, m_expirationDate);
        if (!yearsToMaturity)
        {
            return yearsToMaturity;
        }

        return Strategy::calculateCallDelta({ m_strikePrice, marketData.spotPrice, marketData.volatility, marketData.riskFreeInterestRate, yearsToMaturity.value() });
    }

    template <typename Strategy>
    [[nodiscard]] std::expected<double, Error> putDelta(const MarketData& marketData, const std::chrono::year_month_day& valuationDate) const noexcept
    {
        static_assert(Strategy::supportsOptionStyle(Style), "Pricing strategy does not support the specified option style.");

        const auto yearsToMaturity = Utils::yearsBetween(valuationDate, m_expirationDate);
        if (!yearsToMaturity)
        {
            return yearsToMaturity;
        }

        return Strategy::calculatePutDelta({ m_strikePrice, marketData.spotPrice, marketData.volatility, marketData.riskFreeInterestRate, yearsToMaturity.value() });
    }

    // Properties
    [[nodiscard]] double                      getStrikePrice() const noexcept { return m_strikePrice; }
    [[nodiscard]] std::chrono::year_month_day getExpirationDate() const noexcept { return m_expirationDate; }

private:
    double                      m_strikePrice; // Strike price of the option
    std::chrono::year_month_day m_expirationDate; // Expiration date of the option
};

} // namespace optpriengine
