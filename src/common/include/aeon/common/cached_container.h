// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/common/container.h>
#include <map>
#include <memory>

namespace aeon::common
{

/*!
 * Generic templated base class for cachable objects, like assets. Objects are cached by key.
 * If an object is still referenced anywhere, 'get' will return the existing object,
 * otherwise it will return a nullptr.
 *
 * This class does not take ownership of the cached objects, as it merely stores weak pointers.
 */
template <typename key_t, typename value_t>
class cached_container
{
public:
    using cached_objects = std::map<key_t, std::weak_ptr<value_t>>;

    cached_container() = default;
    ~cached_container() = default;

    cached_container(cached_container<key_t, value_t> &&other) noexcept
        : objects_(other.objects_)
    {
    }

    cached_container<key_t, value_t> &operator=(cached_container<key_t, value_t> &&other) noexcept
    {
        objects_ = std::move(other.objects_);
        return *this;
    }

    cached_container(const cached_container<key_t, value_t> &) noexcept = delete;
    auto operator=(const cached_container<key_t, value_t> &) noexcept -> cached_container<key_t, value_t> & = delete;

    /*!
     * Get a cached object by name. This method will return a shared pointer to the requested object
     * or a nullptr. If the object was found to be expired, a garbage collection will be triggered to
     * clean up expired weak pointers.
     */
    [[nodiscard]] auto get(const key_t &name) -> std::shared_ptr<value_t>
    {
        const auto result = objects_.find(name);

        if (result == objects_.end())
            return nullptr;

        auto object = result->second;

        if (object.expired())
        {
            garbage_collect();
            return nullptr;
        }

        return object.lock();
    }

    /*!
     * Register a newly created object to be cached. If an object with the same name is found, which is not yet expired,
     * an object_cache_name_exception is thrown. This method will take a weak pointer of the given shared pointer to
     * store internally.
     */
    bool add(const key_t &name, const std::shared_ptr<value_t> &obj)
    {
        const auto result = objects_.find(name);

        if (result != objects_.end())
        {
            if (!result->second.expired())
                return false;

            garbage_collect();
        }

        objects_[name] = obj;

        return true;
    }

    /*!
     * Garbage collect all expired cached objects.
     */
    void garbage_collect()
    {
        container::erase_if(objects_, [](const auto &obj) { return obj.second.expired(); });
    }

private:
    cached_objects objects_;
};

} // namespace aeon::common
