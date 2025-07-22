#include "optpriengine/BSMModel.h"
#include "optpriengine/BinomialTreeModel.h"
#include "optpriengine/Option.h"
#include "optpriengine/Utils.h"

#include <chrono>
#include <print>

int main()
{
    const double K = 100.0;
    const double S = 100.0;
    const double sigma = 0.33;
    const double r = 0.03;

    const auto expirationDate = std::chrono::year_month_day(std::chrono::year(2025), std::chrono::month(7), std::chrono::day(17));
    const auto valuationDate = expirationDate - std::chrono::months(1); // 1 month before expiry

    const auto marketData = MarketData { S, sigma, r };

    // Display parameters
    std::println("Parameters:");
    std::println("K: {}", K);
    std::println("S: {}", S);
    std::println("sigma: {}", sigma);
    std::println("r: {}", r);
    std::println("Expiration date: {}", expirationDate);
    std::println("Valuation date: {}", valuationDate);

    const auto yearsToMaturity = Utils::yearsBetween(valuationDate, expirationDate);
    if (!yearsToMaturity) {
        std::println("{}", yearsToMaturity.error().message);
        return 1;
    }
    std::println("Time to maturity: {:.3f} years", yearsToMaturity.value());

    auto europeanOption = Option<OptionStyle::European>(K, expirationDate);

    // Black-Scholes-Merton model
    std::println();
    std::println("Black-Scholes-Merton model:");

    const auto callPriceBSM = europeanOption.callPrice<BSMModel>(marketData, valuationDate);
    if (!callPriceBSM) {
        std::println("{}", callPriceBSM.error().message);
        return 1;
    }

    const auto putPriceBSM = europeanOption.putPrice<BSMModel>(marketData, valuationDate);
    if (!putPriceBSM) {
        std::println("{}", putPriceBSM.error().message);
        return 1;
    }

    std::println("Call price: {:.2f}", callPriceBSM.value());
    std::println("Put price: {:.2f}", putPriceBSM.value());

    // Greeks
    const auto callDeltaBSM = europeanOption.callDelta<BSMModel>(marketData, valuationDate);
    if (!callDeltaBSM) {
        std::println("{}", callDeltaBSM.error().message);
        return 1;
    }

    const auto putDeltaBSM = europeanOption.putDelta<BSMModel>(marketData, valuationDate);
    if (!putDeltaBSM) {
        std::println("{}", putDeltaBSM.error().message);
        return 1;
    }

    std::println("Call delta: {:.4f}", callDeltaBSM.value());
    std::println("Put delta: {:.4f}", putDeltaBSM.value());

    // Binomial tree model (European style option)
    std::println();
    std::println("Binomial tree model (European style option):");

    const size_t numTimeSteps = 1000;

    std::println("Number of time steps: {}", numTimeSteps);

    const auto callPriceEuropeanBinomial = europeanOption.callPrice<BinomialTreeModel<numTimeSteps>>(marketData, valuationDate);
    if (!callPriceEuropeanBinomial) {
        std::println("{}", callPriceEuropeanBinomial.error().message);
        return 1;
    }

    const auto putPriceEuropeanBinomial = europeanOption.putPrice<BinomialTreeModel<numTimeSteps>>(marketData, valuationDate);
    if (!putPriceEuropeanBinomial) {
        std::println("{}", putPriceEuropeanBinomial.error().message);
        return 1;
    }

    std::println("Call price: {:.2f}", callPriceEuropeanBinomial.value());
    std::println("Put price: {:.2f}", putPriceEuropeanBinomial.value());

    // Binomial tree model (American style option)

    auto americanOption = Option<OptionStyle::American>(K, expirationDate);

    std::println();
    std::println("Binomial tree model (American style option):");
    std::println("Number of time steps: {}", numTimeSteps);

    const auto callPriceAmericanBinomial = americanOption.callPrice<BinomialTreeModel<numTimeSteps>>(marketData, valuationDate);
    if (!callPriceAmericanBinomial) {
        std::println("{}", callPriceAmericanBinomial.error().message);
        return 1;
    }

    const auto putPriceAmericanBinomial = americanOption.putPrice<BinomialTreeModel<numTimeSteps>>(marketData, valuationDate);
    if (!putPriceAmericanBinomial) {
        std::println("{}", putPriceAmericanBinomial.error().message);
        return 1;
    }

    std::println("Call price: {:.2f}", callPriceAmericanBinomial.value());
    std::println("Put price: {:.2f}", putPriceAmericanBinomial.value());

    return 0;
}
