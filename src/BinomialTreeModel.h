#pragma once

#include "PricingStrategy.h"

#include <vector>

class BinomialTreeModel : public PricingStrategy
{
public:
    BinomialTreeModel(const int numTimeSteps, const OptionStyle optionStyle);
    ~BinomialTreeModel() override = default;

    double calculateCallPrice(const StrategyParameters strategyParams) override;
    double calculatePutPrice(const StrategyParameters strategyParams) override;

private:
    std::vector<double> calculateAssetPrices(const double S, const double u, const double d, const double dT, const size_t maxNumNodes) const;
    double              getAssetPriceAtNode(const double S, const double u, const double d, const int timeStep, const int nodeIndex) const;

private:
    int m_numTimeSteps;
};
