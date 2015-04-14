#ifndef aeon_streams_stream_name_mixin_h__
#define aeon_streams_stream_name_mixin_h__

namespace aeon
{
namespace streams
{

class stream_name_mixin
{
public:
    stream_name_mixin() :
        name_(AEON_STREAM_DEFAULT_NAME),
        has_name_(false)
    {
    }

    stream_name_mixin(const std::string &name) :
        name_(name),
        has_name_(true)
    {
    }

    std::string get_name()
    {
        return name_;
    }

    void set_name(const std::string name)
    {
        name_ = name;
    }

    bool has_name()
    {
        return has_name_;
    }

private:
    std::string name_;
    bool has_name_;
};

} // namespace streams
} // namespace aeon

#endif // aeon_streams_stream_name_mixin_h__
