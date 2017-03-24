#include <gtest/gtest.h>

#include "dummy_class_mock.hpp"
#include "dummy_class.hpp"

using namespace ::testing;

class DummyClassTest : public Test
{
public:
    DummyClassMock mock;
    DummyClass2 dummy{mock};
};

TEST_F(DummyClassTest, uno)
{
    EXPECT_CALL(mock, dummyFunction(34)).WillOnce(Return(56));
    EXPECT_EQ(56, dummy.get(34));
}
