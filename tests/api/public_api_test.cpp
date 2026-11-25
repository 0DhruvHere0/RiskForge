#include "riskforge/riskforge.hpp"
#include <gtest/gtest.h>
namespace{
    TEST(PublicApiTest, UmbrellaHeaderIsUsable){
        EXPECT_STREQ(riskforge::version(), "0.1.0");
    }
}