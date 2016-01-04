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

mono_assembly::mono_assembly(MonoDomain *domain, const std::string &path) :
    domain_(domain),
    path_(path),
    assembly_(nullptr),
    image_(nullptr)
{
    assembly_ = mono_domain_assembly_open(domain, path.c_str());

    if (!assembly_)
        throw mono_exception();

    image_ = mono_assembly_get_image(assembly_);
}

mono_assembly::~mono_assembly()
{
}

mono_assembly::mono_assembly(mono_assembly &&o) :
    domain_(o.domain_),
    path_(std::move(o.path_)),
    assembly_(o.assembly_),
    image_(o.image_)
{
}

mono_assembly &mono_assembly::operator=(mono_assembly &&o)
{
    domain_ = o.domain_;
    path_ = std::move(o.path_);
    assembly_ = o.assembly_;
    image_ = o.image_;
    return *this;
}

int mono_assembly::execute()
{
    char *argv[1] = { const_cast<char*>(path_.c_str()) };
    return execute(1, argv);
}

int mono_assembly::execute(int argc, char *argv[])
{
    return mono_jit_exec(domain_, assembly_, argc, argv);
}

mono_class mono_assembly::get_class(const std::string &name)
{
    return mono_class(image_, name);
}

mono_class_instance mono_assembly::new_class_instance(const mono_class &cls)
{
    return mono_class_instance(domain_, cls.get_mono_class_ptr());
}

mono_string mono_assembly::new_string(const std::string &str)
{
    return mono_string(domain_, str);
}

} // namespace mono
} // namespace aeon
