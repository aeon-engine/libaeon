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

class mono_assembly;

/*!
 * Class to initialize the Mono JIT. This class must be instanced
 * only once. When this class is deleted, the JIT is cleaned up.
 *
 * Due to the way Mono works, a cleaned up JIT can not be reinitialized
 * at runtime after it was cleaned up. You must keep this class instanced
 * during the full runtime of the application.
 */
class mono_jit : utility::noncopyable
{
public:
    mono_jit();
    ~mono_jit();

    mono_assembly load_assembly(const std::string &path);

private:
    MonoDomain *domain_;
};

} // namespace mono
} // namespace aeon
