#pragma once

#include "OptionStyle.h"
#include "StrategyParameters.h"

#include <cmath>
#include <cstddef>
#include <vector>

template <size_t NumTimeSteps>
class BinomialTreeModel
{
    static_assert(NumTimeSteps > 0, "Number of time steps must be greater than zero.");
    
public:
    [[nodiscard]] inline static constexpr bool supportsOptionStyle(const OptionStyle style) noexcept
    {
        return style == OptionStyle::American || style == OptionStyle::European;
    }

    [[nodiscard]] inline static double calculateCallPrice(const StrategyParameters strategyParams, const OptionStyle optionStyle) noexcept
    {
        auto [S, K, sigma, r, T] = strategyParams;

        const double dt = T / NumTimeSteps;
        const double u = std::exp(sigma * std::sqrt(dt));
        const double d = 1.0 / u;
        const double p = (std::exp(r * dt) - d) / (u - d);

        const size_t maxNumNodes = NumTimeSteps + 1;

        std::vector<double> assetPrices = calculateAssetPrices(S, u, d, dt, maxNumNodes);

        // Initialize call prices at maturity
        std::vector<double> callPrices(maxNumNodes);
        for (size_t i = 0; i < maxNumNodes; ++i)
        {
            callPrices[i] = std::max(0.0, assetPrices[i] - K);
        }

        // Calculate call prices at each time step in place, working backwards
        for (int timeStep = static_cast<int>(NumTimeSteps) - 1; timeStep >= 0; --timeStep)
        {
            for (size_t i = 0; i <= static_cast<size_t>(timeStep); ++i)
            {
                const double earlyExerciseValue = optionStyle == OptionStyle::American ? std::max(0.0, getAssetPriceAtNode(S, u, d, timeStep, i) - K) : 0.0;
                const double callOptionValue = std::exp(-r * dt) * (p * callPrices[i] + (1 - p) * callPrices[i + 1]);
                callPrices[i] = std::max(earlyExerciseValue, callOptionValue);
            }
        }

        return callPrices[0];
    }

    [[nodiscard]] inline static double calculatePutPrice(const StrategyParameters strategyParams, const OptionStyle optionStyle) noexcept
    {
        auto [S, K, sigma, r, T] = strategyParams;

        const double dt = T / NumTimeSteps;
        const double u = std::exp(sigma * std::sqrt(dt));
        const double d = 1.0 / u;
        const double p = (std::exp(r * dt) - d) / (u - d);

        const size_t maxNumNodes = NumTimeSteps + 1;

        std::vector<double> assetPrices = calculateAssetPrices(S, u, d, dt, maxNumNodes);

        // Initialize put prices at maturity
        std::vector<double> putPrices(maxNumNodes);
        for (size_t i = 0; i < maxNumNodes; ++i)
        {
            putPrices[i] = std::max(0.0, K - assetPrices[i]);
        }

        // Calculate put prices at each time step in place, working backwards
        for (int timeStep = static_cast<int>(NumTimeSteps) - 1; timeStep >= 0; --timeStep)
        {
            for (size_t i = 0; i <= static_cast<size_t>(timeStep); ++i)
            {
                const double earlyExerciseValue = optionStyle == OptionStyle::American ? std::max(0.0, K - getAssetPriceAtNode(S, u, d, timeStep, i)) : 0.0;
                const double putOptionValue = std::exp(-r * dt) * (p * putPrices[i] + (1 - p) * putPrices[i + 1]);
                putPrices[i] = std::max(earlyExerciseValue, putOptionValue);
            }
        }

        return putPrices[0];
    }

private:
    [[nodiscard]] inline static std::vector<double> calculateAssetPrices(const double S, const double u, const double d, const double dT, const size_t maxNumNodes) noexcept
    {
        std::vector<double> assetPrices(maxNumNodes);
        for (size_t i = 0; i < maxNumNodes; ++i)
        {
            // 0th element is the highest possible asset price
            assetPrices[i] = S * std::pow(u, static_cast<int>(NumTimeSteps) - i) * std::pow(d, i);
        }

        return assetPrices;
    }

    [[nodiscard]] inline static double getAssetPriceAtNode(const double S, const double u, const double d, const int timeStep, const int nodeIndex) noexcept
    {
        return S * std::pow(u, timeStep - nodeIndex) * std::pow(d, nodeIndex);
    }
};
