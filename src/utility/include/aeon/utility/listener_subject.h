// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <algorithm>
#include <vector>

namespace aeon::utility
{

/*!
 * Base class for the subject of a observer pattern (listener class).
 * Observers are not specificly implemented since the pattern states that
 * only "Update()" is allowed. We want to be a little bit more generic,
 * hence the template.
 *
 * It's up to the implemented class to iterate over the listeners_ vector
 * and call the appropriate methods.
 */
template <typename T>
class listener_subject
{
public:
    listener_subject() = default;
    virtual ~listener_subject() = default;

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
    void attach_listener(T *listener)
    {
        listeners_.push_back(listener);
    }

    /*!
     * Remove a listener/observer from this subject. If this pointer was not previously attached, nothing happens.
     *
     * This will not delete the object, but merely detach it.
     */
    void detach_listener(T *listener)
    {
        listeners_.erase(std::remove(listeners_.begin(), listeners_.end(), listener), listeners_.end());
    }

    /*!
     * Detach all attached listeners.
     *
     * This will not delete the objects, but merely detach them.
     */
    void detach_all_listeners()
    {
        listeners_.clear();
    }

protected:
    std::vector<T *> listeners_;
};

} // namespace aeon::utility
