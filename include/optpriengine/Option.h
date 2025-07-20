#pragma once

#include "OptionStyle.h"
#include "StrategyParameters.h"
#include "Utils.h"

#include <chrono>

struct MarketData {
    double spotPrice; // Current price of the underlying asset
    double volatility; // Volatility of the underlying asset (% per year)
    double riskFreeInterestRate; // Risk-free interest rate (% per year)
};

template <OptionStyle Style>
class Option {
public:
    explicit Option(const double strikePrice, const std::chrono::year_month_day& expirationDate) noexcept
        : m_strikePrice(strikePrice), m_expirationDate(expirationDate) {}

    // Pricing
    template <typename Strategy>
    [[nodiscard]] double callPrice(const MarketData& marketData, const std::chrono::year_month_day& valuationDate) const noexcept {
        static_assert(Strategy::supportsOptionStyle(Style), "Pricing strategy does not support the specified option style.");
        return Strategy::calculateCallPrice({ m_strikePrice, marketData.spotPrice, marketData.volatility, marketData.riskFreeInterestRate, Utils::yearsBetween(valuationDate, m_expirationDate) }, Style);
    }

    template <typename Strategy>
    [[nodiscard]] double putPrice(const MarketData& marketData, const std::chrono::year_month_day& valuationDate) const noexcept {
        static_assert(Strategy::supportsOptionStyle(Style), "Pricing strategy does not support the specified option style.");
        return Strategy::calculatePutPrice({ m_strikePrice, marketData.spotPrice, marketData.volatility, marketData.riskFreeInterestRate, Utils::yearsBetween(valuationDate, m_expirationDate) }, Style);
    }

    // Greeks
    template <typename Strategy>
    [[nodiscard]] double callDelta(const MarketData& marketData, const std::chrono::year_month_day& valuationDate) const noexcept {
        static_assert(Strategy::supportsOptionStyle(Style), "Pricing strategy does not support the specified option style.");
        return Strategy::calculateCallDelta({ m_strikePrice, marketData.spotPrice, marketData.volatility, marketData.riskFreeInterestRate, Utils::yearsBetween(valuationDate, m_expirationDate) });
    }

    template <typename Strategy>
    [[nodiscard]] double putDelta(const MarketData& marketData, const std::chrono::year_month_day& valuationDate) const noexcept {
        static_assert(Strategy::supportsOptionStyle(Style), "Pricing strategy does not support the specified option style.");
        return Strategy::calculatePutDelta({ m_strikePrice, marketData.spotPrice, marketData.volatility, marketData.riskFreeInterestRate, Utils::yearsBetween(valuationDate, m_expirationDate) });
    }

    // Properties
    [[nodiscard]] double getStrikePrice() const noexcept { return m_strikePrice; }
    [[nodiscard]] std::chrono::year_month_day getExpirationDate() const noexcept { return m_expirationDate; }

private:
    double m_strikePrice; // Strike price of the option
    std::chrono::year_month_day m_expirationDate; // Expiration date of the option
};
