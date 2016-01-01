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

#include <aeon/mono.h>

namespace aeon
{
namespace mono
{

mono_gchandle::mono_gchandle() :
    handle_(0)
{
}

mono_gchandle::mono_gchandle(MonoObject *object) :
    handle_(0)
{
    handle_ = mono_gchandle_new(object, 1);
}

mono_gchandle::mono_gchandle(MonoString *object) :
    handle_(0)
{
    handle_ = mono_gchandle_new(reinterpret_cast<MonoObject*>(object), 1);
}

mono_gchandle::~mono_gchandle()
{
    if (handle_ != 0)
        mono_gchandle_free(handle_);
}

mono_gchandle::mono_gchandle(mono_gchandle &&o) :
    handle_(o.handle_)
{
}

mono_gchandle &mono_gchandle::operator=(mono_gchandle &&o)
{
    handle_ = o.handle_;
    return *this;
}

} // namespace mono
} // namespace aeon
