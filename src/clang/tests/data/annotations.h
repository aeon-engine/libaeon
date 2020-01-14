// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <aeon/reflection/annotate.h>

namespace aeon::testing
{

class test_class1
{
public:
    int a;
    float b;
};

class AEON_ANNOTATE(serialize) test_class2
{
public:
    int a;
    float b;
};

class AEON_ANNOTATE(serialize) AEON_ANNOTATE(something_else) test_class3
{
public:
    int a;
    AEON_ANNOTATE(ignore) float b;
};

} // namespace aeon::testing
