#ifndef aeon_utility_singleton_h__
#define aeon_utility_singleton_h__

#define aeon_utility_initialize_singleton(type) \
    template <> std::unique_ptr<type> aeon::utility::singleton<type>::instance_ = nullptr

namespace aeon
{
namespace utility
{

template <class type>
class singleton
{
public:
    singleton()
    {
        assert(instance_ == nullptr);
        instance_ = std::unique_ptr<type>(static_cast<type *>(this));

        if (!instance_)
            throw std::runtime_error("Singleton could not be created.");
    }

    virtual ~singleton()
    {
    }

    static type *create()
    {
        return new type;
    }

    static void dispose()
    {
        instance_ = nullptr;
    }

    static type & get_singleton()
    {
        assert(instance_);

        if (!instance_)
            throw std::runtime_error("Singleton instance is null.");

        return *instance_;
    }

    static type * get_singleton_ptr()
    {
        return instance_;
    }

protected:
    static std::unique_ptr<type> instance_;
};

} // namespace utility
} // namespace aeon

#endif // aeon_utility_singleton_h__
