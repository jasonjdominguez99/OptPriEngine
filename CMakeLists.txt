cmake_minimum_required(VERSION 3.21)
project(OptPriEngine VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Only disable Apple-specific flags if using GCC on macOS
if(APPLE AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "Using GCC on macOS - disabling Apple-specific flags")
    set(CMAKE_OSX_ARCHITECTURES "")
    set(CMAKE_OSX_SYSROOT "")
    set(CMAKE_OSX_DEPLOYMENT_TARGET "")
endif()

# Create the library
add_library(OptPriEngine
    src/PricingEngine.cpp
    src/BSMModel.cpp
    src/BinomialTreeModel.cpp
)

# Public headers
target_include_directories(OptPriEngine PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Private headers
target_include_directories(OptPriEngine PRIVATE
    include/optpriengine
)

option(BUILD_EXAMPLES "Build example programs" ON)
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Make library installable
install(TARGETS OptPriEngine
    EXPORT OptPriEngineTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/ DESTINATION include)
