#include <gtest/gtest.h>
//#pragma clang diagnostic push
//#pragma clang diagnostic ignored "-Weverything"
#include <fakeit.hpp>
//#pragma clang diagnostic pop

#include "dummy_class.hpp"

using namespace ::testing;
using namespace ::fakeit;

class DummyClassTest : public Test
{
public:
    void SetUp() override
    {
        When(Method(mock, dummyFunction)).Return(56);
    }
    Mock<DummyInterface> mock;
    DummyClass2 dummy{mock.get()};
};

TEST_F(DummyClassTest, uno)
{
    EXPECT_EQ(56, dummy.get(34));
    Verify(Method(mock, dummyFunction).Using(34));
}
