#include "BSMModel.h"
#include "PricingEngine.h"
#include <iostream>

int main()
{
    std::cout << "Hello, World!" << std::endl;

    auto engine = PricingEngine(std::make_unique<BSMModel>());

    const auto S = 100.0;
    const auto K = 100.0;
    const auto sigma = 0.2;
    const auto r = 0.05;
    const auto T = 1.0;

    const auto callPrice = engine.calculateCallPrice({ K, S, sigma, r, T });

    // Display parameters
    std::cout << "Parameters:" << std::endl;
    std::cout << "S: " << S << std::endl;
    std::cout << "K: " << K << std::endl;
    std::cout << "sigma: " << sigma << std::endl;
    std::cout << "r: " << r << std::endl;
    std::cout << "T: " << T << std::endl;

    // Display call price
    std::cout << "Call price: " << callPrice << std::endl;

    return 0;
}
