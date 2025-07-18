#pragma once

#include "OptionStyle.h"

#include <vector>

struct StrategyParameters;

class BinomialTreeModel
{
public:
    BinomialTreeModel(const int numTimeSteps) : 
        m_numTimeSteps(numTimeSteps > 0 ? numTimeSteps : 1) // silently enforce minimum number of time steps
    {};

    [[nodiscard]] static constexpr bool supportsOptionStyle(const OptionStyle style) noexcept
    {
        return style == OptionStyle::American || style == OptionStyle::European;
    }

    [[nodiscard]] double calculateCallPrice(const StrategyParameters strategyParams, const OptionStyle optionStyle) const noexcept;
    [[nodiscard]] double calculatePutPrice(const StrategyParameters strategyParams, const OptionStyle optionStyle) const noexcept;

private:
    [[nodiscard]] std::vector<double> calculateAssetPrices(const double S, const double u, const double d, const double dT, const size_t maxNumNodes) const noexcept;
    [[nodiscard]] double              getAssetPriceAtNode(const double S, const double u, const double d, const int timeStep, const int nodeIndex) const noexcept;

private:
    int m_numTimeSteps;
};
