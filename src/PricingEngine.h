#pragma once

#include <memory>

class PricingStrategy;
struct StrategyParameters;

class PricingEngine
{
public:
    PricingEngine(std::unique_ptr<PricingStrategy>&& pricingStrategy);

    double calculateCallPrice(const StrategyParameters strategyParams);

private:
    std::unique_ptr<PricingStrategy> m_pricingStrategy;
};
