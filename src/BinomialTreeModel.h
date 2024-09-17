#pragma once

#include "PricingStrategy.h"

#include <cstddef>

class BinomialTreeModel : public PricingStrategy
{
public:
    BinomialTreeModel(const size_t numTimeSteps);
    ~BinomialTreeModel() override = default;

    double calculateCallPrice(const StrategyParameters strategyParams) override;
    double calculatePutPrice(const StrategyParameters strategyParams) override;

private:
    size_t m_numTimeSteps;
};
