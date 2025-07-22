#pragma once

#include "OptionStyle.h"

namespace optpriengine
{

struct StrategyParameters;

class BSMModel
{
public:
    [[nodiscard]] static constexpr bool supportsOptionStyle(const OptionStyle style) noexcept
    {
        return style == OptionStyle::European;
    }

    [[nodiscard]] static double calculateCallPrice(const StrategyParameters strategyParams, const OptionStyle optionStyle) noexcept;
    [[nodiscard]] static double calculatePutPrice(const StrategyParameters strategyParams, const OptionStyle optionStyle) noexcept;
    [[nodiscard]] static double calculateCallDelta(const StrategyParameters strategyParams) noexcept;
    [[nodiscard]] static double calculatePutDelta(const StrategyParameters strategyParams) noexcept;
};

} // namespace optpriengine
