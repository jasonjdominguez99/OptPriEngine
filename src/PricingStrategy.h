#pragma once

struct StrategyParameters
{
    double strikePrice;
    double spotPrice;
    double volatility; // % per year
    double riskFreeInterestRate; // % per year
    double timeToMaturity; // years
};

enum class OptionStyle
{
    American,
    European
};

class PricingStrategy
{
public:
    explicit PricingStrategy(const OptionStyle optionStyle) noexcept :
        m_optionStyle(optionStyle) {};
    virtual ~PricingStrategy() = default;

    virtual double calculateCallPrice(const StrategyParameters strategyParams) = 0;
    virtual double calculatePutPrice(const StrategyParameters strategyParams) = 0;

protected:
    OptionStyle m_optionStyle;
};
