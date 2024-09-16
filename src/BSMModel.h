#pragma once

#include "PricingStrategy.h"

class BSMModel : public PricingStrategy
{
public:
    ~BSMModel() override = default;

    double calculateCallPrice(const StrategyParameters strategyParams) override;
    double calculatePutPrice(const StrategyParameters strategyParams) override;
};
