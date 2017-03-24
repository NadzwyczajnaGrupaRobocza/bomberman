#pragma once

class DummyClass
{
public:
    virtual ~DummyClass() = default;
    virtual int dummyFunction(int) const;
};

class DummyClass2
{
public:
    DummyClass2(DummyClass& d)
        : dummy{d}{}

    int get(int i) const;

private:
    DummyClass& dummy;
};
