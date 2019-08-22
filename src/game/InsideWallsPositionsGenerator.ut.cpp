#include "gmock/gmock.h"

#include "FieldSize.hpp"
#include "InsideWallsPositionsGenerator.hpp"
#include "gtest/gtest.h"
#include "range/v3/all.hpp"

using namespace ::testing;

class inside_walls_positions_generator_test : public Test
{
public:
    inside_walls_positions_generator generator;
};
