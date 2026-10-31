#include "riskforge/random/philox.hpp"
#include <cstddef>
#include <gtest/gtest.h>
namespace{
    using riskforge::random::Philox4x32_10;
    void expect_block(
        const Philox4x32_10::Counter& counter,
        const Philox4x32_10::Key& key,
        const Philox4x32_10::Block& expected
    )
    {
        const auto actual= Philox4x32_10::generate(counter, key);
        for (std::size_t index=0; index<actual.size(); ++index){
            EXPECT_EQ(actual[index], expected[index]) << "Mismatch as output word "<< index;
        }
    }
    TEST(Philox4x32Test, MatchesRandom123ZeroCounterAndKey){
        expect_block(
            {
                0x00000000u,
                0x00000000u,
                0x00000000u,
                0x00000000u
            },
            {
                0x00000000u,
                0x00000000u
            },
            {
                0x6627E8D5u,
                0xE169C58Du,
                0xBC57AC4Cu,
                0x9B00DBD8u
            }
        );
    }
    TEST(Philox4x32Test, MatchesRandom123AllOnesInput){
        expect_block(
            {
                0xFFFFFFFFu,
                0xFFFFFFFFu,
                0xFFFFFFFFu,
                0xFFFFFFFFu
            },
            {
                0xFFFFFFFFu,
                0xFFFFFFFFu
            },
            {
                0x408F276Du,
                0x41C83B0Eu,
                0xA20BC7C6u,
                0x6D5451FDu
            }
        );
    }
    TEST(Philox4x32Test, MatchesRandom123NonTrivialInput){
        expect_block(
            {
                0x243F6A88u,
                0x85A308D3u,
                0x13198A2Eu,
                0x03707344u
            },
            {
                0xA4093822u,
                0x299F31D0u
            },
            {
                0xD16CFE09u,
                0x94FDCCEBu,
                0x5001E420u,
                0x24126EA1u
            }
        );
    }
}