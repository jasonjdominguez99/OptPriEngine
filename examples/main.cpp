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
    std::println("Time to maturity: {:.3f} years", Utils::yearsBetween(valuationDate, expirationDate));

    auto europeanOption = Option<OptionStyle::European>(K, expirationDate);

    // Black-Scholes-Merton model
    std::println();
    std::println("Black-Scholes-Merton model:");

    const double callPriceBSM = europeanOption.callPrice<BSMModel>(marketData, valuationDate);
    const double putPriceBSM = europeanOption.putPrice<BSMModel>(marketData, valuationDate);

    std::println("Call price: {:.2f}", callPriceBSM);
    std::println("Put price: {:.2f}", putPriceBSM);

    // Greeks
    const double callDeltaBSM = europeanOption.callDelta<BSMModel>(marketData, valuationDate);
    const double putDeltaBSM = europeanOption.putDelta<BSMModel>(marketData, valuationDate);

    std::println("Call delta: {:.4f}", callDeltaBSM);
    std::println("Put delta: {:.4f}", putDeltaBSM);

    // Binomial tree model (European style option)
    std::println();
    std::println("Binomial tree model (European style option):");

    const size_t numTimeSteps = 1000;

    std::println("Number of time steps: {}", numTimeSteps);

    const double callPriceEuropeanBinomial = europeanOption.callPrice<BinomialTreeModel<numTimeSteps>>(marketData, valuationDate);
    const double putPriceEuropeanBinomial = europeanOption.putPrice<BinomialTreeModel<numTimeSteps>>(marketData, valuationDate);

    std::println("Call price: {:.2f}", callPriceEuropeanBinomial);
    std::println("Put price: {:.2f}", putPriceEuropeanBinomial);

    // Binomial tree model (American style option)

    auto americanOption = Option<OptionStyle::American>(K, expirationDate);

    std::println();
    std::println("Binomial tree model (American style option):");
    std::println("Number of time steps: {}", numTimeSteps);

    const double callPriceAmericanBinomial = americanOption.callPrice<BinomialTreeModel<numTimeSteps>>(marketData, valuationDate);
    const double putPriceAmericanBinomial = americanOption.putPrice<BinomialTreeModel<numTimeSteps>>(marketData, valuationDate);
    
    std::println("Call price: {:.2f}", callPriceAmericanBinomial);
    std::println("Put price: {:.2f}", putPriceAmericanBinomial);

    return 0;
}
