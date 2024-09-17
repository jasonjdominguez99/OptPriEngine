#include "BinomialTreeModel.h"

#include <cmath>
#include <vector>

BinomialTreeModel::BinomialTreeModel(const size_t numTimeSteps) :
    m_numTimeSteps(numTimeSteps)
{
}

double BinomialTreeModel::calculateCallPrice(const StrategyParameters strategyParams)
{
    auto [S, K, r, sigma, T] = strategyParams;

    const auto dt = T / m_numTimeSteps;
    const auto u = std::exp(sigma * std::sqrt(dt));
    const auto d = 1.0 / u;
    const auto p = (std::exp(r * dt) - d) / (u - d);

    const auto maxNumNodes = m_numTimeSteps + 1;

    // Calculate possible asset prices at maturity
    std::vector<double> assetPrices(maxNumNodes);
    for (size_t i = 0; i < maxNumNodes; ++i)
    {
        // 0th element is the highest possible asset price
        assetPrices[i] = S * std::pow(u, m_numTimeSteps - i) * std::pow(d, i);
    }

    // Initialize call prices at maturity
    std::vector<double> callPrices(maxNumNodes);
    for (size_t i = 0; i < maxNumNodes; ++i)
    {
        callPrices[i] = std::max(0.0, assetPrices[i] - K);
    }

    // Calculate call prices at each time step in place, working bakwards
    for (int timeStep = m_numTimeSteps - 1; timeStep >= 0; --timeStep)
    {
        for (size_t i = 0; i <= timeStep; ++i)
        {
            callPrices[i] = std::exp(-r * dt) * (p * callPrices[i] + (1 - p) * callPrices[i + 1]);
        }
    }

    return callPrices[0];
}

double BinomialTreeModel::calculatePutPrice(const StrategyParameters strategyParams)
{
    return 0.0;
}
