// Copyright (c) 2012-2019 Robin Degen

#include <aeon/mono/mono_jit.h>
#include <aeon/mono/mono_assembly.h>
#include <aeon/mono/mono_exception.h>
#include <mono_build_config.h>

#include <mono/metadata/assembly.h>

namespace aeon::mono
{

mono_assembly mono_jit::internal_call_assembly_;

mono_jit::mono_jit()
    : mono_jit{"AeonMono"}
{
}

mono_jit::mono_jit(const std::string &domain)
    : domain_{nullptr}
{
    mono_set_dirs(AEON_MONO_ASSEMBLY_DIR, AEON_MONO_CONFIG_DIR);
    domain_ = mono_jit_init(domain.c_str());

    if (!domain_)
        throw mono_exception{};
}

mono_jit::~mono_jit()
{
    // FIXME #35 Calling mono_jit_cleanup causes deadlock
    // if (domain_)
    //    mono_jit_cleanup(domain_);
}

auto mono_jit::load_assembly(const std::string &path) const -> mono_assembly
{
    auto assembly = mono_assembly{domain_, path};

    if (!internal_call_assembly_.valid())
        internal_call_assembly_ = mono_assembly{domain_, assembly.get_mono_assembly_ptr()};

    return assembly;
}

void mono_jit::set_auto_wrap_assembly(const mono_assembly &assembly)
{
    internal_call_assembly_ = mono_assembly{assembly.get_mono_domain_ptr(), assembly.get_mono_assembly_ptr()};
}

auto mono_jit::get_auto_wrap_assembly() -> mono_assembly &
{
    return internal_call_assembly_;
}

void mono_jit::__add_internal_call(const std::string &name, const void *func)
{
    mono_add_internal_call(name.c_str(), func);
}

} // namespace aeon::mono
