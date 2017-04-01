#include "dummy_class.hpp"

int DummyClass::dummyFunction(int i) const
{
    return 2 * i;
}

int DummyClass2::get(int i) const
{
    return dummy.dummyFunction(i);
}
