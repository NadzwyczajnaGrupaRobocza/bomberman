#include "gtest/gtest.h"

#include "BasicMap.hpp"

using namespace ::testing;

TEST(BasicMapTest, BasicMapShouldInheritFromMap)
{
    auto testFunction = [](const Map& ) {};
    BasicMap map;
    testFunction(map);
}
