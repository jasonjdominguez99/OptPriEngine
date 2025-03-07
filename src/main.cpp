#include "BSMModel.h"
#include "BinomialTreeModel.h"
#include "PricingEngine.h"
#include <iostream>

int main()
{
    const double K = 100.0;
    const double S = 100.0;
    const double sigma = 0.33;
    const double r = 0.03;
    const double T = 1.0 / 12.0; // 1 month

    const auto strategyParams = StrategyParameters { K, S, sigma, r, T };

    // Display parameters
    std::cout << "Parameters:" << std::endl;
    std::cout << "K: " << K << std::endl;
    std::cout << "S: " << S << std::endl;
    std::cout << "sigma: " << sigma << std::endl;
    std::cout << "r: " << r << std::endl;
    std::cout << "T: " << T << std::endl;

    auto engine = PricingEngine(std::make_unique<BSMModel>());

    // Black-Scholes-Merton model
    std::cout << "\nBlack-Scholes-Merton model:" << std::endl;
    const double callPriceBSM = engine.calculateCallPrice(strategyParams);
    std::cout << "Call price: " << callPriceBSM << std::endl;
    const double putPriceBSM = engine.calculatePutPrice(strategyParams);
    std::cout << "Put price: " << putPriceBSM << std::endl;

    // Binomial tree model (European style option)
    std::cout << "\nBinomial tree model (European style option):" << std::endl;
    const int numTimeSteps = 1000;
    engine.setPricingStrategy(std::make_unique<BinomialTreeModel>(numTimeSteps, OptionStyle::European));
    std::cout << "Number of time steps: " << numTimeSteps << std::endl;
    const double callPriceEuropeanBinomial = engine.calculateCallPrice(strategyParams);
    std::cout << "Call price: " << callPriceEuropeanBinomial << std::endl;
    const double putPriceEuropeanBinomial = engine.calculatePutPrice(strategyParams);
    std::cout << "Put price: " << putPriceEuropeanBinomial << std::endl;

    // Binomial tree model (American style option)
    std::cout << "\nBinomial tree model (American style option):" << std::endl;
    engine.setPricingStrategy(std::make_unique<BinomialTreeModel>(numTimeSteps, OptionStyle::American));
    std::cout << "Number of time steps: " << numTimeSteps << std::endl;
    const double callPriceAmericanBinomial = engine.calculateCallPrice(strategyParams);
    std::cout << "Call price: " << callPriceAmericanBinomial << std::endl;
    const double putPriceAmericanBinomial = engine.calculatePutPrice(strategyParams);
    std::cout << "Put price: " << putPriceAmericanBinomial << std::endl;

    return 0;
}
