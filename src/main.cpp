#include "BSMModel.h"
#include "BinomialTreeModel.h"
#include "PricingEngine.h"
#include <iostream>

int main()
{
    const double S = 100.0;
    const double K = 100.0;
    const double sigma = 0.2;
    const double r = 0.05;
    const double T = 1.0;

    const auto strategyParams = StrategyParameters { K, S, sigma, r, T };

    // Display parameters
    std::cout << "Parameters:" << std::endl;
    std::cout << "S: " << S << std::endl;
    std::cout << "K: " << K << std::endl;
    std::cout << "sigma: " << sigma << std::endl;
    std::cout << "r: " << r << std::endl;
    std::cout << "T: " << T << std::endl;

    auto engine = PricingEngine(std::make_unique<BSMModel>());

    // Black-Scholes-Merton model
    std::cout << "\nBlack-Scholes-Merton model:" << std::endl;
    const double callPriceBSM = engine.calculateCallPrice(strategyParams);
    std::cout << "Call price: " << callPriceBSM << std::endl;

    // Binomial tree model
    std::cout << "\nBinomial tree model:" << std::endl;
    const size_t numTimeSteps = 1000;
    engine.setPricingStrategy(std::make_unique<BinomialTreeModel>(numTimeSteps));
    std::cout << "Number of time steps: " << numTimeSteps << std::endl;
    const double callPriceBinomial = engine.calculateCallPrice(strategyParams);
    std::cout << "Call price: " << callPriceBinomial << std::endl;

    return 0;
}
