// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/mono/mono_assembly.h>
#include <aeon/mono/mono_exception.h>
#include <aeon/mono/mono_class.h>
#include <aeon/mono/mono_class_instance.h>
#include <aeon/mono/mono_string.h>
#include <mono/metadata/assembly.h>

namespace aeon::mono
{

mono_assembly::mono_assembly() noexcept
    : domain_{nullptr}
    , assembly_{nullptr}
    , image_{nullptr}
{
}

mono_assembly::mono_assembly(MonoDomain *domain, MonoAssembly *assembly) noexcept
    : domain_{domain}
    , assembly_{assembly}
    , image_{mono_assembly_get_image(assembly_)}
{
}

mono_assembly::mono_assembly(MonoDomain *domain, const std::string &path)
    : domain_{domain}
    , assembly_{nullptr}
    , image_{nullptr}
{
    assembly_ = mono_domain_assembly_open(domain, path.c_str());

    if (!assembly_)
        throw mono_exception{};

    image_ = mono_assembly_get_image(assembly_);
}

mono_assembly::~mono_assembly() = default;

mono_assembly::mono_assembly(mono_assembly &&) noexcept = default;

auto mono_assembly::operator=(mono_assembly &&) noexcept -> mono_assembly & = default;

[[nodiscard]] auto mono_assembly::get_mono_assembly_ptr() const noexcept -> MonoAssembly *
{
    return assembly_;
}

[[nodiscard]] auto mono_assembly::get_mono_domain_ptr() const noexcept -> MonoDomain *
{
    return domain_;
}

[[nodiscard]] auto mono_assembly::get_class(const std::string &name) const -> mono_class
{
    return mono_class{this, image_, name};
}

[[nodiscard]] auto mono_assembly::get_class(const std::string &name_space, const std::string &name) const -> mono_class
{
    return mono_class{this, image_, name_space, name};
}

[[nodiscard]] auto mono_assembly::new_class_instance(const mono_class &cls) const noexcept -> mono_class_instance
{
    return mono_class_instance{this, domain_, cls.get_mono_class_ptr()};
}

[[nodiscard]] auto mono_assembly::new_string(const std::string &str) const noexcept -> mono_string
{
    return mono_string{domain_, str};
}

[[nodiscard]] auto mono_assembly::valid() const noexcept -> bool
{
    return domain_ != nullptr && assembly_ != nullptr && image_ != nullptr;
}

} // namespace aeon::mono
