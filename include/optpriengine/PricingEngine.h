#pragma once

#include "StrategyParameters.h"

#include <memory>

enum class OptionStyle;

template <typename Strategy>
class PricingEngine
{
public:
    explicit PricingEngine(Strategy&& pricingStrategy) noexcept 
        : m_pricingStrategy(std::move(pricingStrategy)) {}

    [[nodiscard]] static constexpr bool supportsOptionStyle(const OptionStyle style) noexcept
    {
        return Strategy::supportsOptionStyle(style);
    }

    [[nodiscard]] double calculateCallPrice(const StrategyParameters strategyParams, const OptionStyle optionStyle) const noexcept
    {
        return m_pricingStrategy.calculateCallPrice(strategyParams, optionStyle);
    }

    [[nodiscard]] double calculatePutPrice(const StrategyParameters strategyParams, const OptionStyle optionStyle) const noexcept
    {
        return m_pricingStrategy.calculatePutPrice(strategyParams, optionStyle);
    }

private:
    Strategy m_pricingStrategy;
};
