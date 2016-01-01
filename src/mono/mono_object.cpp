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

mono_object::mono_object(MonoDomain *domain, MonoClass *cls) :
    object_(nullptr),
    class_(cls),
    handle_(0)
{
    object_ = mono_object_new(domain, cls);
    mono_runtime_object_init(object_);
    handle_ = mono_gchandle_new(object_, 1);
}

mono_object::~mono_object()
{
    mono_gchandle_free(handle_);
}

mono_method mono_object::get_method(const std::string &name, int argc /*= 0*/)
{
    return mono_method(class_, object_, name, argc);
}

} // namespace mono
} // namespace aeon
