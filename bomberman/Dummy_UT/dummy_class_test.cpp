#include <iostream>
#include <iterator>
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <fakeit.hpp>
#include <range/v3/all.hpp>

#include "dummy_class.hpp"

using ::testing::Test;
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

TEST(Rangev3, range)
{
    const auto NaturalNumberSet = ranges::view::ints(0);
    const auto digits = NaturalNumberSet | ranges::view::take(10);

    std::cout << "the digits...\n";
    ranges::copy(digits, ranges::ostream_iterator<int>(std::cout, " "));
    std::cout << "\nthats odd.. very odd...\n";

    ranges::copy(NaturalNumberSet | ranges::view::filter([](const auto i) {
                     return i % 2 == 1;
                 }) | ranges::view::take(42),
                 ranges::ostream_iterator<int>(std::cout, " "));

    std::cout << "\nand the prime suspects are...\n";

    const auto prime_number = [](const auto n) {
        return (n < 3)
                   ? false
                   : ranges::all_of(ranges::view::ints(2, n - 1),
                                    [n](const auto i) { return n % i != 0; });
    };

    ranges::copy(ranges::view::ints(3) | ranges::view::filter(prime_number) |
                     ranges::view::take(13),
                 ranges::ostream_iterator<int>(std::cout, " "));

    std::cout << '\n';
}

TEST_F(DummyClassTest, CanUseHamcrestNotation)
{
  ASSERT_THAT(DummyClass{}.returnAlways5(), ::testing::Eq(5));
}
