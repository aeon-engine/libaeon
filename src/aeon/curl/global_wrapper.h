/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
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
namespace curl
{

class global_wrapper;
typedef std::shared_ptr<global_wrapper> global_wrapper_ptr;

class global_wrapper : public utility::noncopyable
{
public:
    global_wrapper();
    ~global_wrapper();

    static global_wrapper_ptr get();

protected:
    bool initialized_;
    static std::mutex mutex_;
    static global_wrapper_ptr wrapper_;
};

} // namespace curl
} // namespace aeon
