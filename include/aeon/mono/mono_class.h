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

class mono_method;

class mono_class : public utility::noncopyable
{
public:
    mono_class(MonoImage *image, const std::string &name);
    ~mono_class();

    mono_class(mono_class &&o);
    mono_class &operator=(mono_class &&o);

    mono_method get_method(const std::string &name, int argc = 0);

    MonoClass *get_mono_class_ptr() const;

private:
    MonoImage *image_;
    std::string name_;
    MonoClass *class_;
};

} // namespace mono
} // namespace aeon
