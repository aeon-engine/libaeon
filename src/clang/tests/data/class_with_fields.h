// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

namespace aeon::testing
{

class test_class;

struct unknown_type;
struct fake_static_type;

class test_class
{
public:
    int public_member1;
    float public_member2;
    unknown_type public_member3;
    auto public_member4 = 5;
    const double public_member5 = 1337.0;

    static fake_static_type public_static_member;

    mutable int public_mutable_member;

protected:
    int protected_member1;
    float protected_member2;

private:
    int private_member1;
    float private_member2;
};

} // namespace aeon::testing
