#pragma once

class DummyInterface
{
public:
    virtual ~DummyInterface() = default;
    virtual int dummyFunction(int) const = 0;
};

class DummyClass : public DummyInterface
{
public:
    int dummyFunction(int) const override;
};

class DummyClass2
{
public:
    DummyClass2(DummyInterface& d)
        : dummy{d}{}

    int get(int i) const;

private:
    DummyInterface& dummy;
};
