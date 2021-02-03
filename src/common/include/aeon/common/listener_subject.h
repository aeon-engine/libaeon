// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <algorithm>
#include <vector>

namespace aeon::common
{

/*!
 * Subject of a observer pattern (listener class).
 */
template <typename T>
class listener_subject final
{
public:
    listener_subject() = default;
    ~listener_subject() = default;

    listener_subject(listener_subject<T> &&) = default;
    auto operator=(listener_subject<T> &&) -> listener_subject<T> & = default;

    listener_subject(const listener_subject<T> &) = default;
    auto operator=(const listener_subject<T> &) -> listener_subject<T> & = default;

    /*!
     * Attach a listener/observer to this subject.
     *
     * This does not take ownership of this pointer, so it's up to
     * the caller to keep this pointer alive, and delete it appropriately.
     */
    void attach(T &listener)
    {
        listeners_.push_back(&listener);
    }

    /*!
     * Remove a listener/observer from this subject. If this pointer was not previously attached, nothing happens.
     *
     * This will not delete the object, but merely detach it.
     */
    void detach(T &listener)
    {
        listeners_.erase(std::remove(std::begin(listeners_), std::end(listeners_), &listener), std::end(listeners_));
    }

    /*!
     * Detach all attached listeners.
     *
     * This will not delete the objects, but merely detach them.
     */
    void detach_all()
    {
        listeners_.clear();
    }

    /*!
     * Invoke a method in every attached listener
     */
    template <typename func_t, class... args_t>
    void invoke_each(func_t &&func, args_t &&...args)
    {
        for (const auto &listener : listeners_)
            std::invoke(func, listener, std::forward<args_t>(args)...);
    }

    /*!
     * Access all attached listeners
     */
    [[nodiscard]] const auto &listeners() const noexcept
    {
        return listeners_;
    }

private:
    std::vector<T *> listeners_;
};

} // namespace aeon::common
