#include "Map.hpp"

#include <gtest/gtest.h>

using namespace ::testing;

class ConcreteMap : public Map
{
};

TEST(MapTest, MapShouldBeCreated)
{
    ASSERT_NO_THROW(ConcreteMap{});
}
