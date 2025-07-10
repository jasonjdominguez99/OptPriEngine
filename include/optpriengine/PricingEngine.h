#pragma once

#include <memory>

class PricingStrategy;
struct StrategyParameters;

class PricingEngine
{
public:
    explicit PricingEngine(std::unique_ptr<PricingStrategy>&& pricingStrategy) noexcept;

    [[nodiscard]] double calculateCallPrice(const StrategyParameters strategyParams) const;
    [[nodiscard]] double calculatePutPrice(const StrategyParameters strategyParams) const;

    void setPricingStrategy(std::unique_ptr<PricingStrategy>&& pricingStrategy);

private:
    std::unique_ptr<PricingStrategy> m_pricingStrategy;
};
