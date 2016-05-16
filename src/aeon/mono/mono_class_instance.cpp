/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
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

mono_class_instance::mono_class_instance(MonoDomain *domain, MonoClass *cls)
    : mono_object(domain)
    , object_(nullptr)
    , class_(cls)
{
    object_ = mono_object_new(domain, cls);
    mono_runtime_object_init(object_);
    handle_ = mono_gchandle(object_);
}

mono_class_instance::~mono_class_instance()
{
}

mono_class_instance::mono_class_instance(mono_class_instance &&o)
    : mono_object(std::move(o))
    , object_(o.object_)
    , class_(o.class_)
{
}

mono_class_instance &mono_class_instance::operator=(mono_class_instance &&o)
{
    mono_object::operator=(std::move(o));
    object_ = o.object_;
    class_ = o.class_;
    return *this;
}

mono_method mono_class_instance::get_method(const std::string &name, int argc /*= 0*/)
{
    return mono_method(class_, object_, name, argc);
}

MonoObject *mono_class_instance::get_mono_object() const
{
    return object_;
}

} // namespace mono
} // namespace aeon
