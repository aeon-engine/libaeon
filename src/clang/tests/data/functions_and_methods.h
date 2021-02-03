// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <string>

namespace aeon::testing
{

class test_class
{
public:
    test_class();
    ~test_class();

    double public_method();
    static int public_static_method();
};

std::string normal_function();
static double static_function();
inline int inlined_function()
{
}

} // namespace aeon::testing
