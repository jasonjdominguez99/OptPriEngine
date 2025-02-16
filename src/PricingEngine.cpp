#include "PricingEngine.h"

#include "PricingStrategy.h"

PricingEngine::PricingEngine(std::unique_ptr<PricingStrategy>&& pricingStrategy) noexcept :
    m_pricingStrategy(std::move(pricingStrategy))
{
}

double PricingEngine::calculateCallPrice(const StrategyParameters strategyParams) const
{
    return m_pricingStrategy->calculateCallPrice(strategyParams);
}

double PricingEngine::calculatePutPrice(const StrategyParameters strategyParams) const
{
    return m_pricingStrategy->calculatePutPrice(strategyParams);
}

void PricingEngine::setPricingStrategy(std::unique_ptr<PricingStrategy>&& pricingStrategy)
{
    m_pricingStrategy = std::move(pricingStrategy);
}
