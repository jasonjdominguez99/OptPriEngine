#pragma once

struct StrategyParameters
{
    double strikePrice;
    double spotPrice;
    double volatility; // % per year
    double riskFreeInterestRate; // % per year
    double timeToMaturity; // years
};

class PricingStrategy
{
public:
    virtual ~PricingStrategy() = default;

    virtual double calculateCallPrice(const StrategyParameters strategyParams) = 0;
    virtual double calculatePutPrice(const StrategyParameters strategyParams) = 0;
};
