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
#include <mono_build_config.h>

namespace aeon
{
namespace mono
{

mono_jit::mono_jit()
    : mono_jit("AeonMono")
{
}

mono_jit::mono_jit(const std::string &domain)
    : domain_(nullptr)
{
    mono_set_dirs(AEON_MONO_ASSEMBLY_DIR, AEON_MONO_CONFIG_DIR);
    domain_ = mono_jit_init(domain.c_str());

    if (!domain_)
        throw mono_exception();
}

mono_jit::~mono_jit()
{
    mono_jit_cleanup(domain_);
}

mono_assembly mono_jit::load_assembly(const std::string &path) const
{
    return mono_assembly(domain_, path);
}

} // namespace mono
} // namespace aeon
