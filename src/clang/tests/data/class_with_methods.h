// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <string>

namespace aeon::testing
{

struct unknown_type1;
struct unknown_type2;
struct unknown_type3;

class test_class
{
public:
    test_class();
    test_class(int arg1, float arg2);
    ~test_class();

    void public_method1();
    int public_method2(int arg1, float arg2) noexcept;
    int public_method2(int arg1, float arg2, std::string arg3);
    void public_method3(unknown_type1 arg1);

protected:
    void protected_method1();
    int protected_method2(int arg1, float arg2, std::string arg3);
    void protected_method3(unknown_type2 arg1);

private:
    void private_method1();
    int private_method2(int arg1, float arg2, std::string arg3);
    void private_method3(unknown_type3 arg1);
};

} // namespace aeon::testing
