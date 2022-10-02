// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <vector>
#include <string>
#include <cstring>

namespace aeon::common
{

// Simple wrapper to convert a vector of strings to a char*[].
class parameters
{
public:
    explicit parameters(std::vector<std::string> &params)
        : argc_(0)
        , argv_(new char *[params.size()])
    {
        for (auto &param : params)
        {
            argv_[argc_] = new char[param.size() + 1];
            memcpy(argv_[argc_], param.data(), param.size() + 1);
            ++argc_;
        }
    }

    ~parameters()
    {
        if (!argv_)
            return;

        for (int i = 0; i < argc_; ++i)
        {
            delete[] argv_[i];
        }

        delete[] argv_;
    }

    parameters(const parameters &) = delete;
    auto operator=(const parameters &) -> parameters & = delete;

    parameters(parameters &&other) noexcept
        : argc_{other.argc_}
        , argv_{other.argv_}
    {
        other.argc_ = 0;
        other.argv_ = nullptr;
    }

    parameters &operator=(parameters &&other) noexcept
    {
        argc_ = other.argc_;
        argv_ = other.argv_;
        other.argc_ = 0;
        other.argv_ = nullptr;
        return *this;
    }

    auto argc() const
    {
        return argc_;
    }

    auto argv() const
    {
        return argv_;
    }

private:
    int argc_;
    char **argv_;
};

} // namespace aeon::common
