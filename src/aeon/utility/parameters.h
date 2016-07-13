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
namespace utility
{

// Simple wrapper to convert a vector of strings to a char*[].
class parameters
{
public:
    explicit parameters(std::vector<std::string> &params)
        : argc_(0)
        , argv_(new char*[params.size()])
    {
        for (auto &param : params)
        {
            argv_[argc_] = new char[param.size()];
            memcpy(argv_[argc_], param.data(), param.size());
            ++argc_;
        }
    }

    ~parameters()
    {
        if (!argv_)
            return;

        for (int i = 0; i < argc_; ++i)
        {
            delete [] argv_[i];
        }

        delete [] argv_;
    }

    int argc() const
    {
        return argc_;
    }

    const char * const*argv() const
    {
        return argv_;
    }

private:
    int argc_;
    char **argv_;
};

} // namespace utility
} // namespace aeon
