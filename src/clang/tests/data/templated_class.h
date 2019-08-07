// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

namespace aeon::testing
{

class test_class
{
public:
    test_class();
    ~test_class();

    void public_method();

protected:
    void protected_method();

private:
    void private_method();
};

template <typename T, typename U>
class test_class2
{
public:
    test_class2();
    ~test_class2();

    void public_method();

protected:
    void protected_method();

private:
    void private_method();
};

} // namespace aeon::testing
