/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#pragma once

#define aeon_utility_initialize_singleton(type) \
    template <> std::unique_ptr<type> aeon::utility::singleton<type>::instance_ = nullptr

namespace aeon
{
namespace utility
{

template <class type>
class singleton : public utility::noncopyable
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
