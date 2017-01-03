/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
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

namespace aeon
{
namespace utility
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
    /*!
     * Constructor
     */
    listener_subject() = default;

    /*!
     * Destructor
     */
    virtual ~listener_subject() = default;

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

} // namespace utility
} // namespace aeon
