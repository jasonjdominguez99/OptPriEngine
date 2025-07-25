#include "BSMModel.h"

#include "StrategyParameters.h"

#include <cmath>

namespace optpriengine
{

namespace
{
double normalCDF(const double x)
{
    return 0.5 * (1 + std::erf(x / std::sqrt(2)));
}
}

double BSMModel::calculateCallPrice(const StrategyParameters strategyParams, const OptionStyle /*optionStyle*/) noexcept
{
    auto [K, S, sigma, r, T] = strategyParams;

    const double d1 = (std::log(S / K) + (r + 0.5 * std::pow(sigma, 2)) * T) / (sigma * std::sqrt(T));
    const double d2 = d1 - sigma * sqrt(T);

    return S * normalCDF(d1) - K * std::exp(-r * T) * normalCDF(d2);
}

double BSMModel::calculatePutPrice(const StrategyParameters strategyParams, const OptionStyle /*optionStyle*/) noexcept
{
    auto [K, S, sigma, r, T] = strategyParams;

    const double d1 = (std::log(S / K) + (r + 0.5 * std::pow(sigma, 2)) * T) / (sigma * std::sqrt(T));
    const double d2 = d1 - sigma * sqrt(T);

    return K * std::exp(-r * T) * normalCDF(-d2) - S * normalCDF(-d1);
}

double BSMModel::calculateCallDelta(const StrategyParameters strategyParams) noexcept
{
    auto [K, S, sigma, r, T] = strategyParams;

    const double d1 = (std::log(S / K) + (r + 0.5 * std::pow(sigma, 2)) * T) / (sigma * std::sqrt(T));

    return normalCDF(d1);
}

double BSMModel::calculatePutDelta(const StrategyParameters strategyParams) noexcept
{
    auto [K, S, sigma, r, T] = strategyParams;

    const double d1 = (std::log(S / K) + (r + 0.5 * std::pow(sigma, 2)) * T) / (sigma * std::sqrt(T));

    return -normalCDF(-d1);
}

} // namespace optpriengine
