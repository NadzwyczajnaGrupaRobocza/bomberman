#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "fakeit.hpp"

#include "BoundaryWallsPositionsGenerator.hpp"

using namespace ::fakeit;
using namespace ::testing;

class BoundaryWallsPositionsGeneratorTest : public Test
{
public:
    BoundaryWallsPositionsGenerator generator;
};

TEST_F(BoundaryWallsPositionsGeneratorTest, Dummy)
{
    ASSERT_FALSE(false);
}
