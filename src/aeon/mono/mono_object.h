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

class mono_object : public utility::noncopyable
{
public:
    mono_object(MonoDomain *domain);
    ~mono_object();

    mono_object(mono_object &&o);
    mono_object &operator=(mono_object &&o);

    virtual MonoObject *get_mono_object() const = 0;

protected:
    MonoDomain *domain_;
    mono_gchandle handle_;
};

} // namespace mono
} // namespace aeon
