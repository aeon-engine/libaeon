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

#pragma once

namespace aeon
{
namespace mono
{

class mono_object : public utility::noncopyable
{
public:
    mono_object(MonoDomain *domain, MonoClass *cls);
    ~mono_object();

    mono_object(mono_object &&o);
    mono_object &operator=(mono_object &&o);

    mono_method get_method(const std::string &name, int argc = 0);

private:
    MonoObject *object_;
    MonoClass *class_;
    mono_gchandle handle_;
};

} // namespace mono
} // namespace aeon
