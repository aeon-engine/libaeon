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

class mono_method : public utility::noncopyable
{
public:
    mono_method(MonoClass *cls, const std::string &name, int argc);
    mono_method(MonoClass *cls, MonoObject *object, const std::string &name, int argc);

    ~mono_method();

    mono_method(mono_method &&o);
    mono_method &operator=(mono_method &&o);

    void operator()();

private:
    MonoClass *class_;
    std::string name_;
    int argc_;
    MonoMethod *method_;
    MonoObject *object_;
};

} // namespace mono
} // namespace aeon
