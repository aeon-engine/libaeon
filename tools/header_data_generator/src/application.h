// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

namespace aeon::header_data_generator
{

class application final
{
public:
    application() = default;
    ~application() = default;

    application(const application &) = delete;
    auto operator=(const application &) -> application & = delete;

    application(application &&o) noexcept = delete;
    auto operator=(application &&o) noexcept -> application & = delete;

    auto main(const int argc, char *argv[]) noexcept -> int;
};

} // namespace aeon::header_data_generator
