#pragma once

#include <memory>

class PricingStrategy;
struct StrategyParameters;

class PricingEngine
{
public:
    PricingEngine(std::unique_ptr<PricingStrategy>&& pricingStrategy);

    double calculateCallPrice(const StrategyParameters strategyParams);
    double calculatePutPrice(const StrategyParameters strategyParams);

    void setPricingStrategy(std::unique_ptr<PricingStrategy>&& pricingStrategy);

private:
    std::unique_ptr<PricingStrategy> m_pricingStrategy;
};
