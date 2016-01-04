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

mono_class::mono_class(MonoImage *image, const std::string &name)
    : image_(image)
    , name_(name)
    , class_(nullptr)
{
    class_ = mono_class_from_name(image, "", name.c_str());
}

mono_class::~mono_class()
{
}

mono_class::mono_class(mono_class &&o)
    : image_(o.image_)
    , name_(std::move(o.name_))
    , class_(o.class_)
{
}

mono_class &mono_class::operator=(mono_class &&o)
{
    image_ = o.image_;
    name_ = std::move(o.name_);
    class_ = o.class_;
    return *this;
}

mono_method mono_class::get_method(const std::string &name, int argc /*= 0*/)
{
    return mono_method(class_, name, argc);
}

MonoClass *mono_class::get_mono_class_ptr() const
{
    return class_;
}

} // namespace mono
} // namespace aeon
