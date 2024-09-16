#include "PricingEngine.h"

#include "PricingStrategy.h"

PricingEngine::PricingEngine(std::unique_ptr<PricingStrategy>&& pricingStrategy) :
    m_pricingStrategy(std::move(pricingStrategy))
{
}

double PricingEngine::calculateCallPrice(const StrategyParameters strategyParams)
{
    return m_pricingStrategy->calculateCallPrice(strategyParams);
}
