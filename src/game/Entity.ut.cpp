#include "Entity.hpp"

#include "gtest/gtest.h"
#include "gmock/gmock-matchers.h"

class ConcreteEntity : public Entity
{
public:
    void update(DeltaTime) override
    {
        ASSERT_TRUE(true);
    }

    bool areYouDead() const override
    {
        return false;
    }
};

using namespace ::testing;

TEST(EntityInterfaceTest, shouldUpdate)
{
    using namespace std::literals::chrono_literals;
    ConcreteEntity{}.update(123ms);
}

TEST(EntityInterfaceTest, shouldTellThatNotDead)
{
    constexpr auto notDead = false;
    ASSERT_THAT(ConcreteEntity{}.areYouDead(), Eq(notDead));
}
