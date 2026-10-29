add_test([=[RiskForgeSmokeTest.TestFrameworkIsWorking]=]  /Users/dhruvgupta/Projects/RiskForge/build/debug/tests/riskforge_tests [==[--gtest_filter=RiskForgeSmokeTest.TestFrameworkIsWorking]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RiskForgeSmokeTest.TestFrameworkIsWorking]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/dhruvgupta/Projects/RiskForge/tests/smoke_test.cpp:2]==]
    WORKING_DIRECTORY [==[/Users/dhruvgupta/Projects/RiskForge/build/debug/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
set(riskforge_tests_TESTS [==[RiskForgeSmokeTest.TestFrameworkIsWorking]==])
