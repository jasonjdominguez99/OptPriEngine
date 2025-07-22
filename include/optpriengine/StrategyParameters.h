#pragma once

#include "OptionStyle.h"

namespace optpriengine
{

struct StrategyParameters
{
    double strikePrice;
    double spotPrice;
    double volatility; // % per year
    double riskFreeInterestRate; // % per year
    double timeToMaturity; // years
};

} // namespace optpriengine
