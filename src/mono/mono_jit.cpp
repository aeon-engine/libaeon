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

mono_jit::mono_jit()
    : domain_(nullptr)
{
    domain_ = mono_jit_init("AeonMono");

    if (!domain_)
        throw mono_exception();
}

mono_jit::~mono_jit()
{
    mono_jit_cleanup(domain_);
}

mono_assembly mono_jit::load_assembly(const std::string &path)
{
    return mono_assembly(domain_, path);
}

} // namespace mono
} // namespace aeon
