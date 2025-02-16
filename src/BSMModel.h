#pragma once

#include "PricingStrategy.h"

class BSMModel : public PricingStrategy
{
public:
    explicit BSMModel() :
        PricingStrategy(OptionStyle::European) {}; // BSM model only applies to European style options
    ~BSMModel() override = default;

    double calculateCallPrice(const StrategyParameters strategyParams) override;
    double calculatePutPrice(const StrategyParameters strategyParams) override;
};
