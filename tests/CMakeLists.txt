include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(INSTALL_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
add_executable(riskforge_tests
    smoke_test.cpp
    random/philox_test.cpp
)
target_compile_features(riskforge_tests 
    PRIVATE 
        cxx_std_20
)
target_link_libraries(riskforge_tests
    PRIVATE
        riskforge
        GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(riskforge_tests)