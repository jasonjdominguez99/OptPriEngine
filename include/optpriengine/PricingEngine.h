#pragma once

#include "StrategyParameters.h"

#include <memory>

enum class OptionStyle;

template <typename Strategy>
class PricingEngine
{
public:
    [[nodiscard]] static constexpr bool supportsOptionStyle(const OptionStyle style) noexcept
    {
        return Strategy::supportsOptionStyle(style);
    }

    [[nodiscard]] double calculateCallPrice(const StrategyParameters strategyParams, const OptionStyle optionStyle) const noexcept
    {
        return Strategy::calculateCallPrice(strategyParams, optionStyle);
    }

    [[nodiscard]] double calculatePutPrice(const StrategyParameters strategyParams, const OptionStyle optionStyle) const noexcept
    {
        return Strategy::calculatePutPrice(strategyParams, optionStyle);
    }
};
