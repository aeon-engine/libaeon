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

#include <aeon/mono.h>

namespace aeon
{
namespace mono
{

mono_object::mono_object(MonoDomain *domain)
    : domain_(domain)
{
}

mono_object::~mono_object()
{
}

mono_object::mono_object(mono_object &&o)
    : domain_(o.domain_)
    , handle_(std::move(o.handle_))
{
}

mono_object &mono_object::operator=(mono_object &&o)
{
    domain_ = o.domain_;
    handle_ = std::move(o.handle_);
    return *this;
}

} // namespace mono
} // namespace aeon
