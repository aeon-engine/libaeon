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

class mono_string : public mono_object
{
public:
    mono_string(MonoDomain *domain, const std::string &str);
    ~mono_string();

    mono_string(mono_string &&o);
    mono_string &operator=(mono_string &&o);

    mono_string &operator=(const std::string &str);

    MonoObject *get_mono_object() const override;

private:
    MonoString *object_;
    std::string string_;
};

} // namespace mono
} // namespace aeon
