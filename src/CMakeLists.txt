# Minimum required version of CMake
cmake_minimum_required(VERSION 3.21)

# Project name
project(OptPriEngine)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add all the source files for your project
add_executable(OptPriEngine main.cpp PricingEngine.cpp BSMModel.cpp BinomialTreeModel.cpp)
