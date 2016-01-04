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

mono_string::mono_string(MonoDomain *domain, const std::string &str) :
    mono_object(domain),
    object_(nullptr),
    string_(str)
{
    object_ = mono_string_new(domain, str.c_str());
    handle_ = mono_gchandle(object_);
}

mono_string::~mono_string()
{
}

mono_string::mono_string(mono_string &&o) :
    mono_object(std::move(o)),
    object_(o.object_),
    string_(std::move(o.string_))
{
}

mono_string &mono_string::operator=(mono_string &&o)
{
    mono_object::operator=(std::move(o));
    object_ = o.object_;
    string_ = std::move(o.string_);
    return *this;
}

mono_string &mono_string::operator=(const std::string &str)
{
    string_ = str;
    object_ = mono_string_new(domain_, str.c_str());
    handle_ = mono_gchandle(object_);
    return *this;
}

MonoObject *mono_string::get_mono_object() const
{
    return reinterpret_cast<MonoObject*>(object_);
}

} // namespace mono
} // namespace aeon
