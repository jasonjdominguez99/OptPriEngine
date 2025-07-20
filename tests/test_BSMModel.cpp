#include <gtest/gtest.h>
#include "optpriengine/BSMModel.h"
#include "optpriengine/StrategyParameters.h"

TEST(BSMModelTest, DummyTest) {
    EXPECT_TRUE(true);
}

TEST(BSMModelTest, DeltaCallPutParity) {
    const StrategyParameters params = {100.0, 100.0, 0.2, 0.05, 1.0};

    double callDelta = BSMModel::calculateCallDelta(params);
    double putDelta = BSMModel::calculatePutDelta(params);

    EXPECT_NEAR(callDelta - putDelta, 1, 1e-6);
}
