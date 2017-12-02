#include <gtest/gtest.h>

template <auto A> auto f(int b) -> decltype(A)
{
	return A + b;
}

TEST(Cpp17, AutoTemplateArgument)
{
	EXPECT_EQ(2, f<1>(1));
}

