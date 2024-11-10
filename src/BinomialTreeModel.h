#pragma once

#include "PricingStrategy.h"

#include <cstddef>

class BinomialTreeModel : public PricingStrategy
{
public:
    BinomialTreeModel(const int numTimeSteps);
    ~BinomialTreeModel() override = default;

    double calculateCallPrice(const StrategyParameters strategyParams) override;
    double calculatePutPrice(const StrategyParameters strategyParams) override;

private:
    int m_numTimeSteps;
};
