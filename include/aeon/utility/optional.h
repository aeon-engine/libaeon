#ifndef aeon_utility_optional_h__
#define aeon_utility_optional_h__

namespace aeon
{
namespace utility
{

template <typename T>
class optional
{
public:
    optional() :
        value_(),
        has_value_(false)
    {
    }

    optional(T val) :
        value_(val),
        has_value_(true)
    {
    }

    bool has_value()
    {
        return has_value_;
    }

    void reset()
    {
        has_value_ = false;
    }

    operator T()
    {
        if (!has_value_)
            throw std::runtime_error("optional variable has no value.");

        return value_;
    }

private:
    T value_;
    bool has_value_;
};

} // namespace utility
} // namespace aeon

#endif // aeon_utility_optional_h__
