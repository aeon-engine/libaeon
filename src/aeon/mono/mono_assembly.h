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

#pragma once

namespace aeon
{
namespace mono
{

class mono_class;
class mono_class_instance;
class mono_string;

class mono_assembly : public utility::noncopyable
{
public:
    explicit mono_assembly(MonoDomain *domain, const std::string &path);
    ~mono_assembly();

    mono_assembly(mono_assembly &&o);
    mono_assembly &operator=(mono_assembly &&o);

    int execute();
    int execute(int argc, char *argv[]);

    mono_class get_class(const std::string &name);
    mono_class_instance new_class_instance(const mono_class &cls);
    mono_string new_string(const std::string &str);

private:
    MonoDomain *domain_;
    std::string path_;
    MonoAssembly *assembly_;
    MonoImage *image_;
};

} // namespace mono
} // namespace aeon
