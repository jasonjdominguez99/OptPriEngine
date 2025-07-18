#pragma once

#include "OptionStyle.h"

struct StrategyParameters;

class BSMModel
{
public:
    [[nodiscard]] static constexpr bool supportsOptionStyle(const OptionStyle style) noexcept
    {
        return style == OptionStyle::European;
    }

    [[nodiscard]] double calculateCallPrice(const StrategyParameters strategyParams, const OptionStyle optionStyle) const noexcept;
    [[nodiscard]] double calculatePutPrice(const StrategyParameters strategyParams, const OptionStyle optionStyle) const noexcept;
};
