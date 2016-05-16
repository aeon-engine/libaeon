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

mono_method::mono_method(MonoClass *cls, const std::string &name, int argc)
    : class_(cls)
    , name_(name)
    , argc_(argc)
    , method_(nullptr)
    , object_(nullptr)
{
    method_ = mono_class_get_method_from_name(cls, name.c_str(), argc);
}

mono_method::mono_method(MonoClass *cls, MonoObject *object, const std::string &name, int argc)
    : class_(cls)
    , name_(name)
    , argc_(argc)
    , method_(nullptr)
    , object_(object)
{
    method_ = mono_class_get_method_from_name(cls, name.c_str(), argc);
}

mono_method::~mono_method()
{
}

mono_method::mono_method(mono_method &&o)
    : class_(o.class_)
    , name_(std::move(o.name_))
    , argc_(o.argc_)
    , method_(o.method_)
    , object_(o.object_)
{
}

mono_method &mono_method::operator=(mono_method &&o)
{
    class_ = o.class_;
    name_ = std::move(o.name_);
    argc_ = o.argc_;
    method_ = o.method_;
    object_ = o.object_;
    return *this;
}

void mono_method::operator()()
{
    void *params[1] = {nullptr};
    execute(params);
}

void mono_method::operator()(std::vector<mono_object *> params)
{
    std::vector<MonoObject *> real_params;
    for (auto p : params)
    {
        real_params.push_back(p->get_mono_object());
    }

    execute(reinterpret_cast<void **>(real_params.data()));
}

void mono_method::execute(void **params)
{
    MonoObject *ret_value = mono_runtime_invoke(method_, object_, params, nullptr);

    if (!ret_value)
        return;
}

} // namespace mono
} // namespace aeon
