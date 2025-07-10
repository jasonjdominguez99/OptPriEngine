# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        52eb8108c5bdec04579160ae17225d66034bd723 # release-1.17.0
)
FetchContent_MakeAvailable(googletest)

add_executable(OptPriEngine_tests
    test_BSMModel.cpp
    test_BinomialTreeModel.cpp
)

target_link_libraries(OptPriEngine_tests
    OptPriEngine
    GTest::gtest_main
)

# Discover tests for CTest
include(GoogleTest)
gtest_discover_tests(OptPriEngine_tests)
