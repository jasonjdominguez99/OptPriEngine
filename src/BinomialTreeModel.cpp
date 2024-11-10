#include "BinomialTreeModel.h"

#include <cmath>

BinomialTreeModel::BinomialTreeModel(const int numTimeSteps) :
    m_numTimeSteps(numTimeSteps > 0 ? numTimeSteps : 1) // silently enforce minimum number of time steps
{
}

double BinomialTreeModel::calculateCallPrice(const StrategyParameters strategyParams)
{
    auto [S, K, sigma, r, T] = strategyParams;

    const double dt = T / m_numTimeSteps;
    const double u = std::exp(sigma * std::sqrt(dt));
    const double d = 1.0 / u;
    const double p = (std::exp(r * dt) - d) / (u - d);

    const size_t maxNumNodes = static_cast<size_t>(m_numTimeSteps + 1);

    std::vector<double> assetPrices = calculateAssetPrices(S, u, d, dt, maxNumNodes);

    // Initialize call prices at maturity
    std::vector<double> callPrices(maxNumNodes);
    for (size_t i = 0; i < maxNumNodes; ++i)
    {
        callPrices[i] = std::max(0.0, assetPrices[i] - K);
    }

    // Calculate call prices at each time step in place, working bakwards
    for (int timeStep = m_numTimeSteps - 1; timeStep >= 0; --timeStep)
    {
        for (size_t i = 0; i <= static_cast<size_t>(timeStep); ++i)
        {
            callPrices[i] = std::exp(-r * dt) * (p * callPrices[i] + (1 - p) * callPrices[i + 1]);
        }
    }

    return callPrices[0];
}

double BinomialTreeModel::calculatePutPrice(const StrategyParameters strategyParams)
{
    auto [S, K, sigma, r, T] = strategyParams;

    const double dt = T / m_numTimeSteps;
    const double u = std::exp(sigma * std::sqrt(dt));
    const double d = 1.0 / u;
    const double p = (std::exp(r * dt) - d) / (u - d);

    const size_t maxNumNodes = static_cast<size_t>(m_numTimeSteps + 1);

    std::vector<double> assetPrices = calculateAssetPrices(S, u, d, dt, maxNumNodes);

    // Initialize put prices at maturity
    std::vector<double> putPrices(maxNumNodes);
    for (size_t i = 0; i < maxNumNodes; ++i)
    {
        putPrices[i] = std::max(0.0, K - assetPrices[i]);
    }

    // Calculate put prices at each time step in place, working bakwards
    for (int timeStep = m_numTimeSteps - 1; timeStep >= 0; --timeStep)
    {
        for (size_t i = 0; i <= static_cast<size_t>(timeStep); ++i)
        {
            putPrices[i] = std::exp(-r * dt) * (p * putPrices[i] + (1 - p) * putPrices[i + 1]);
        }
    }

    return putPrices[0];
}

std::vector<double> BinomialTreeModel::calculateAssetPrices(const double S, const double u, const double d, const double dT, const size_t maxNumNodes) const
{
    std::vector<double> assetPrices(maxNumNodes);
    for (size_t i = 0; i < maxNumNodes; ++i)
    {
        // 0th element is the highest possible asset price
        assetPrices[i] = S * std::pow(u, m_numTimeSteps - i) * std::pow(d, i);
    }

    return assetPrices;
}
