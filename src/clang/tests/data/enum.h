// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

namespace aeon::testing
{

enum test_enum
{
    test_enum_member1,
    test_enum_member2,
    test_enum_member3 = test_enum_member2
};

enum class test_enum_class
{
    member1,
    member2,
    member3,
    member4 = member3
};

} // namespace aeon::testing
