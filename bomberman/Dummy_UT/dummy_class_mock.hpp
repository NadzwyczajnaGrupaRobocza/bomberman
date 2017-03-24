#pragma once

#include <gmock/gmock.h>

#include "dummy_class.hpp"

class DummyClassMock : public DummyClass
{
public:
    MOCK_CONST_METHOD1(dummyFunction, int(int));
};
